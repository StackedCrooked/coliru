/* ---------------------------- */
/*  艦これシミュレータ Ver.0.1  */
/* ---------------------------- */

/* 【説明】
   パラメータから戦闘結果をシミュレートするソフトウェアデース！
   先人たちが残した種々のデータを元にしています。感謝しますね！
   ちょっと(記述量が)重い感じもしますけれど、でも、頑張ります！
   お役に立ちましたか？　そう、なら、頑張った甲斐がありました！
   【注意事項】
   ・本ソフトによって生じたあらゆる損害に対して責任は持ちません
   ・分からない仕様は推定で書きましたので実際テキトーです
     (対空装備・対空カットインによる撃墜は面倒なので実装していません)
   ・敵が生き残っている際は容赦なく夜戦する仕様です。なお、攻撃目標の
     選択が一様分布なので長門がながもん化していませんのでご安心を
   ・弾着観測攻撃はなるべく早く実装します……
   ・「航空戦と雷撃がなんでターン制なんだよ？」善処します……
   ・演習を想定しています。大破ストッパー？なにそれおいしいの？
   ・テストキャラクターにしばふ艦が適任なのは確定的に明らか
*/

/* プリプロセッサ */
#include <cmath>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <vector>

/* using宣言 */
using std::cout;
using std::setw;
using std::showpos;
using std::string;
using std::vector;

/* 定数宣言 */
// 艦種は、ビットマップを利用して情報を詰め込むようにした
// それぞれ「対潜能力があるか」「水偵等を積めるか」「瑞雲等を積めるか」
// 「艦戦等を積めるか」「開幕雷撃できるか」「魚雷が積めるか」「戦艦か」を示す
const int isAntiSub = 0x01, isAirs = 0x02, isAirs2 = 0x04, isAirs3 = 0x08,
           isFirstTorpedo = 0x10, isTorpedo = 0x20, isBB = 0x40;
enum SC{SC_DD  = isAntiSub + isTorpedo,    							//駆逐艦
        SC_CL  = isAntiSub + isAirs + isTorpedo,					//軽巡洋艦
        SC_CLT = isAntiSub + isAirs + isFirstTorpedo + isTorpedo,	//重雷装巡洋艦
        SC_CA  = isAirs + isTorpedo,								//重巡洋艦
        SC_CAV = isAntiSub + isAirs + isAirs2 + isTorpedo,			//航空巡洋艦
        SC_BB  = isAirs + isBB,										//戦艦
        SC_BBV = isAntiSub + isAirs + isAirs2 + isBB,				//航空戦艦
        SC_CVL = isAntiSub + isAirs + isAirs2 + isAirs3,			//軽空母
        SC_CV  = isAirs + isAirs2 + isAirs3,						//正規空母
        SC_SS  = isFirstTorpedo + isTorpedo,						//潜水艦
        SC_SSV = isAirs + isFirstTorpedo + isTorpedo,				//潜水空母
        SC_AV  = isAntiSub + isAirs + isFirstTorpedo};				//水上機母艦
enum REACH{REACH_NONE, REACH_SHORT, REACH_MEDIUM, REACH_LONG, REACH_VERYLONG};	//射程
enum SPEED{SPEED_LOW, SPEED_HIGH};									//速力
enum FORMATION{FOR_TRAIL, FOR_SUBTRAIL, FOR_CIRCLE, FOR_ECHELON,
               FOR_ABREAST};	//陣形(単縦陣・複縦陣・輪形陣・梯形陣・単横陣)
enum BP{BP_SAME, BP_DIFF, BP_T_Plus, BP_T_Minus};	//交戦形態
const double SearchThreshold = 10.0;								//索敵時のしきい値
enum ANTIAIR{AA_WORST, AA_BAD, AA_NORMAL, AA_GOOD, AA_BEST};		//制空権の状態
const int AttackPlus[] = {12, 12, 17, 20};							//触接による補正値
enum TURN{TURN_AIR, TURN_TOR, TURN_NOON, TURN_NIGHT};				//攻撃タイミング
const int MaxKanmusu = 6;											//1艦における最大艦娘数

/* プロトタイプ宣言 */
string toStrKind(const SC);		//艦種を変換
string toStrReach(const REACH);	//射程を変換
string toStrSpeed(const SPEED);	//速力を変換
string showDamage(const int, const int);	//損害状況を表示
struct kanmusu;
string simulate(const vector<kanmusu>&, const vector<kanmusu>&,
                vector<double>&, vector<double>&);	//シミュレート
struct condition;
void AttackAction(const int Target, const int BaseAttack, const int Level,
                  const vector<kanmusu> &Yours, vector<int> &YoursAlived,
                  vector<condition> &YoursCond, const FORMATION MineForm,
                  const BP BattlePosition, const int HP, const int NowHP,
                  const double NightFire,
                  const int MineAttackPlus, const double FixedShot, const TURN Turn);	//攻撃！

/* 構造体宣言 */
struct weapon{
	// メンバ変数
	string Name;	//名前
	string Kind;	//種別
	int Attack;		//火力
	int Hit;		//命中
	REACH Reach;	//射程
	int Evade;		//回避
	int Bomb;		//爆装
	int Torpedo;	//雷装
	int Search;		//索敵
	int AntiSub;	//対潜
	int AntiAir;	//対空
	int Defense;	//装甲
	// メンバ関数
	//装備に関する情報を表示
	void putInfo();
};
// 装備に関する情報を表示
void weapon::putInfo(){
	cout << "装備名：" << Name << "\n";
	cout << "種別：" << Kind << "\n";
	cout << "火力：" << setw(4) << showpos << Attack << "  雷装：" << setw(4) << showpos << Torpedo << "\n";
	cout << "爆装：" << setw(4) << showpos << Bomb << "  対空：" << setw(4) << showpos << AntiAir << "\n";
	cout << "対潜：" << setw(4) << showpos << AntiSub << "  索敵：" << setw(4) << showpos << Search << "\n";
	cout << "命中：" << setw(4) << showpos << Hit << "  回避：" << setw(4) << showpos << Evade << "\n";
	cout << "射程：" << setw(4) << showpos << toStrReach(Reach) << "  装甲：" << setw(4) << showpos << Defense << "\n\n";
}

struct kanmusu{	// メンバ変数
	string Name;			//名前
	SC Kind;				//艦種
	int Level;				//レベル
	int Slots;				//スロット数
	vector<weapon> Weapons;	//装備
	vector<int> Airs;		//スロット毎の艦載機数
	int HP;					//耐久
	int Attack;				//火力
	int Torpedo;			//雷装
	int AntiAir;			//対空
	int Defense;			//装甲
	int Evade;				//回避
	int AntiSub;			//対潜
	int Search;				//索敵
	REACH Reach;			//射程
	int Luck;				//運
	SPEED Speed;			//速力
	// メンバ関数

	//コンストラクタ
	kanmusu(const string, const SC, const int, const int, const int, const int, 
			const int, const int, const int, const int, const int,
			const int, const REACH, const int, const SPEED);
	//艦娘に関する情報を表示
	void putInfo();
};
// コンストラクタ
kanmusu::kanmusu(const string name, const SC kind, const int level, const int slots,
                 const int hp, const int attack, const int torpedo,
	             const int antiair, const int defense, const int evade,
	             const int antisub, const int search, const REACH reach,
	             const int luck, const SPEED speed){
	std::stringstream ss;
	ss << level;
	Name = name + "Lv" + ss.str();
	Kind = kind;
	Level = level;
	Slots = slots;
	Weapons.resize(slots);
	Airs.resize(slots);
	HP = hp;
	Attack = attack;
	Torpedo = torpedo;
	AntiAir = antiair;
	Defense = defense;
	Evade = evade;
	AntiSub = antisub;
	Search = search;
	Reach = reach;
	Luck = luck;
	Speed = speed;
}
// 艦娘に関する情報を表示
void kanmusu::putInfo(){
	cout << "艦名：" << Name << "\n";
	cout << "艦種：" << toStrKind(Kind) << "\n";
	cout << "スロット数：" << Slots << "\n";
	cout << "装備(艦載機数)：\n";
	for(int i = 0; i < Slots; ++i){
		cout << "  " << Weapons[i].Name << "(" << Airs[i] << ")\n";
	}
	cout << "耐久：" << setw(4) << HP << "  火力：" << setw(4) << Attack << "\n";
	cout << "装甲：" << setw(4) << Defense << "  雷装：" << setw(4) << Torpedo << "\n";
	cout << "回避：" << setw(4) << Evade << "  対空：" << setw(4) << AntiAir << "\n";
	int AirsSum = 0u;
	for(int i = 0; i < Slots; ++i){
		AirsSum += Airs[i];
	}
	cout << "搭載：" << setw(4) << AirsSum << "  対潜：" << setw(4) << AntiSub << "\n";
	cout << "速力：" << toStrSpeed(Speed) << "  索敵：" << setw(4) << Search << "\n";
	cout << "射程：" << setw(4) << toStrReach(Reach) << "   運 ：" << setw(4) << Luck << "\n\n";
}

struct condition{
	int NowHP;				//現在の耐久
	int NowCond;			//現在のコンディション
	vector<int> NowAirs;	//現在の艦載機数
};

/* 関数定義 */
std::random_device rd;
std::mt19937 mt(rd());
std::uniform_real_distribution<> Rand(0.0, 1.0);	//パーセントな分布向け

string toStrKind(const SC Kind){
	switch(Kind){
		case SC_DD:
			return "駆逐艦";
		case SC_CL:
			return "軽巡洋艦";
		case SC_CLT:
			return "重雷装巡洋艦";
		case SC_CA:
			return "重巡洋艦";
		case SC_CAV:
			return "航空巡洋艦";
		case SC_BB:
			return "戦艦";
		case SC_BBV:
			return "航空戦艦";
		case SC_CVL:
			return "軽空母";
		case SC_CV:
			return "正規空母";
		case SC_SS:
			return "潜水艦";
		case SC_SSV:
			return "潜水空母";
		case SC_AV:
			return "水上機母艦";
		default:
			return "不明";
	}
}
string toStrReach(const REACH Reach){
	switch(Reach){
		case REACH_NONE:
			return "―";
		case REACH_SHORT:
			return "短";
		case REACH_MEDIUM:
			return "中";
		case REACH_LONG:
			return "長";
		case REACH_VERYLONG:
			return "超長";
		default:
			return "不明";
	}
}
string toStrSpeed(const SPEED Speed){
	switch(Speed){
		case SPEED_LOW:
			return "低速";
		case SPEED_HIGH:
			return "高速";
		default:
			return "不明";
	}
}
string showDamage(const int NowHP, const int HP){
	if(HP * 0.75 < NowHP){
		return "(健在)";
	} else if(HP * 0.5 < NowHP){
		return "(小破)";
	} else if(HP * 0.25 < NowHP){
		return "(中破)";
	} else if(0 < NowHP){
		return "(大破)";
	} else{
		return "(撃沈)";
	}
}
string simulate(const vector<kanmusu> &Mine, const vector<kanmusu> &Yours,
                const FORMATION MineForm, const FORMATION YoursForm,
                vector<double> &HitPoint1, vector<double> &HitPoint2){
	std::stringstream Logger;
	// 初期設定
	Logger << "【初期設定】\n";
	int MineShips = Mine.size(), YoursShips = Yours.size();
	Logger << "　自軍艦数：" << MineShips;
	switch(MineForm){
		case FOR_TRAIL:
			Logger << "(単縦陣)\n";
			break;
		case FOR_SUBTRAIL:
			Logger << "(複縦陣)\n";
			break;
		case FOR_CIRCLE:
			Logger << "(輪形陣)\n";
			break;
		case FOR_ECHELON:
			Logger << "(梯形陣)\n";
			break;
		case FOR_ABREAST:
			Logger << "(単横陣)\n";
			break;
	}
	for(int i = 0; i < MineShips; ++i){
		Logger << "　　" << Mine[i].Name << "\n";
	}
	Logger << "　敵軍艦数：" << YoursShips;
	switch(YoursForm){
		case FOR_TRAIL:
			Logger << "(単縦陣)\n";
			break;
		case FOR_SUBTRAIL:
			Logger << "(複縦陣)\n";
			break;
		case FOR_CIRCLE:
			Logger << "(輪形陣)\n";
			break;
		case FOR_ECHELON:
			Logger << "(梯形陣)\n";
			break;
		case FOR_ABREAST:
			Logger << "(単横陣)\n";
			break;
	}
	for(int i = 0; i < YoursShips; ++i){
		Logger << "　　" << Yours[i].Name << "\n";
	}
	vector<condition> MineCond(MineShips), YoursCond(YoursShips);	//艦のコンディション
	vector<int> MineAlived(MineShips), YoursAlived(YoursShips);	//生存艦のリスト
	for(int i = 0; i < MineShips; ++i){
		MineCond[i].NowHP = Mine[i].HP;
		MineCond[i].NowCond = 49;
		MineCond[i].NowAirs = Mine[i].Airs;
		MineAlived[i] = i;
	}
	for(int i = 0; i < YoursShips; ++i){
		YoursCond[i].NowHP = Yours[i].HP;
		YoursCond[i].NowCond = 49;
		YoursCond[i].NowAirs = Yours[i].Airs;
		YoursAlived[i] = i;
	}

	/* ---------- */
	/* |戦闘開始| */
	/* ---------- */

	/* 0. 事前設定 */
	// 交戦形態を設定
	//彩雲をチェック
	bool isSaiun = false;
	for(int i = 0; i < MineShips; ++i){
		for(int j = 0; j < Mine[i].Slots; ++j){
			if(Mine[i].Weapons[j].Name == "彩雲"){
				isSaiun = true;
				break;
			}
		}
		if(isSaiun) break;
	}
	for(int i = 0; i < YoursShips; ++i){
		for(int j = 0; j < Yours[i].Slots; ++j){
			if(Yours[i].Weapons[j].Name == "彩雲"){
				isSaiun = true;
				break;
			}
		}
		if(isSaiun) break;
	}
	//乱数で決める
	BP BattlePosition;
	double p = Rand(mt);
	if(p < 0.45){
		BattlePosition = BP_SAME;
	}else if(p < 0.75){
		BattlePosition = BP_DIFF;
	}else if(p < 0.90){
		BattlePosition = BP_T_Plus;
	}else{
		BattlePosition = BP_T_Minus;
	}
	if((isSaiun) && (BattlePosition == BP_T_Minus)) BattlePosition = BP_DIFF;

	/* 1. 索敵フェイズ */
	Logger << "【索敵フェイズ】\n";
	// 自分の索敵値を計算する
	int SearchAirs = 0, SearchRadars = 0, SearchOther = 0;
	for(int i = 0; i < MineShips; ++i){
		SearchOther += Mine[i].Search;
		for(int j = 0; j < Mine[i].Slots; ++j){
			if(((Mine[i].Weapons[j].Kind == "水偵") || (Mine[i].Weapons[j].Kind == "水爆")) && (Mine[i].Airs[j] != 0)){
				SearchAirs += Mine[i].Weapons[j].Search;
			}
			if(Mine[i].Weapons[j].Kind == "電探"){
				SearchRadars += Mine[i].Weapons[j].Search;
			}
		}
	}
	double SearchScore = SearchAirs * 2 + SearchRadars + sqrt(SearchOther);
	Logger << "　自軍索敵値：" << SearchScore << "\n";
	// 索敵が成功したかを判定する
	//(実装としては「しきい値≦索敵値なら成功」としている)
	bool isSearchSuccess;
	if(SearchScore >= SearchThreshold){
		isSearchSuccess = true;
		Logger << "　策敵結果：成功\n";
	}else{
		isSearchSuccess = false;
		Logger << "　策敵結果：失敗\n";
	}

	/* 2. 航空戦・制空権フェイズ */
	Logger << "【航空戦・制空権フェイズ】\n";
	// 自分と相手の制空値を計算する
	Logger << "○制空権\n";
	int MineAntiAirScore = 0, YoursAntiAirScore = 0;
	bool hasMineAntiAir = false, hasYoursAntiAir = false;	//艦載機を積んでいるか
	for(int i = 0; i < MineShips; ++i){
		for(int j = 0; j < Mine[i].Slots; ++j){
			if((Mine[i].Weapons[j].Kind == "艦戦") || (Mine[i].Weapons[j].Kind == "艦攻")
			|| (Mine[i].Weapons[j].Kind == "艦爆") || (Mine[i].Weapons[j].Kind == "水爆")
			|| (Mine[i].Weapons[j].Kind == "爆戦")){
				MineAntiAirScore += sqrt(MineCond[i].NowAirs[j]) * Mine[i].Weapons[j].AntiAir;
				if(MineCond[i].NowAirs[j] > 0) hasMineAntiAir = true;
			}
		}
	}
	for(int i = 0; i < YoursShips; ++i){
		for(int j = 0; j < Yours[i].Slots; ++j){
			if((Yours[i].Weapons[j].Kind == "艦戦") || (Yours[i].Weapons[j].Kind == "艦攻")
			|| (Yours[i].Weapons[j].Kind == "艦爆") || (Yours[i].Weapons[j].Kind == "水爆")
			|| (Yours[i].Weapons[j].Kind == "爆戦")){
				YoursAntiAirScore += sqrt(YoursCond[i].NowAirs[j]) * Yours[i].Weapons[j].AntiAir;
				if(YoursCond[i].NowAirs[j] > 0) hasYoursAntiAir = true;
			}
		}
	}
	Logger << "　自軍制空値：" << MineAntiAirScore << "\n";
	Logger << "　敵軍制空値：" << YoursAntiAirScore << "\n";
	// 制空権の結果を判定
	ANTIAIR AntiAirResult;
	Logger << "　結果：";
	if(((hasMineAntiAir == false) || (isSearchSuccess == false)) && (hasYoursAntiAir == false)){
		Logger << "　航空均衡\n";
		AntiAirResult = AA_NORMAL;
	}else if(MineAntiAirScore >= YoursAntiAirScore * 3){
		Logger << "　制空権確保\n";
		AntiAirResult = AA_BEST;
	}else if(MineAntiAirScore * 2 >= YoursAntiAirScore * 3){
		Logger << "　航空優勢\n";
		AntiAirResult = AA_GOOD;
	}else if(MineAntiAirScore * 3 >= YoursAntiAirScore * 2){
		Logger << "　航空均衡\n";
		AntiAirResult = AA_NORMAL;
	}else if(MineAntiAirScore * 3 >= YoursAntiAirScore){
		Logger << "　航空劣勢\n";
		AntiAirResult = AA_BAD;
	}else{
		Logger << "　制空権喪失\n";
		AntiAirResult = AA_WORST;
	}
	// 制空権により触接の判定が行われる
	//(実は微妙に実装を端折ったというのは秘密)
	Logger << "○触接判定\n";
	bool isMineTrailer = false, isYoursTrailer = false;
	int MineAttackPlus = 0, YoursAttackPlus = 0;
	for(int i = 0; i < MineShips; ++i){
		for(int j = 0; j < Mine[i].Slots; ++j){
			if((Mine[i].Weapons[j].Kind == "水偵") || (Mine[i].Weapons[j].Kind == "艦偵")
			|| (Mine[i].Weapons[j].Kind == "艦攻")){
				if(MineCond[i].NowAirs[j] > 0) isMineTrailer = true;
			}
		}
	}
	for(int i = 0; i < YoursShips; ++i){
		for(int j = 0; j < Yours[i].Slots; ++j){
			if((Yours[i].Weapons[j].Kind == "水偵") || (Yours[i].Weapons[j].Kind == "艦偵")
			|| (Yours[i].Weapons[j].Kind == "艦攻")){
				if(YoursCond[i].NowAirs[j] > 0) isYoursTrailer = true;
			}
		}
	}
	if(AntiAirResult == AA_WORST) isMineTrailer = false;
	if(AntiAirResult == AA_BEST) isYoursTrailer = false;
	Logger << "　自軍触接：";
	if(isMineTrailer){
		Logger << "可能(";
		for(int i = 0; i < MineShips; ++i){
			for(int j = 0; j < Mine[i].Slots; ++j){
				if((Mine[i].Weapons[j].Kind == "水偵") && (Rand(mt) <= 0.2)){
					if(MineCond[i].NowAirs[j] > 0) MineAttackPlus = AttackPlus[Mine[i].Weapons[j].Hit];
				}else if((Mine[i].Weapons[j].Kind == "艦偵") && (Rand(mt) <= 0.5)){
					if(MineCond[i].NowAirs[j] > 0) MineAttackPlus = AttackPlus[Mine[i].Weapons[j].Hit];
				}else if((Mine[i].Weapons[j].Kind == "艦攻") && (Rand(mt) <= 0.02)){
					if(MineCond[i].NowAirs[j] > 0) MineAttackPlus = AttackPlus[Mine[i].Weapons[j].Hit];
				}
				if(MineAttackPlus != 0) break;
			}
			if(MineAttackPlus != 0) break;
		}
		if(MineAttackPlus != 0){
			Logger << "成功 +" << MineAttackPlus << ")\n";
		}else{
			Logger << "失敗)\n";
		}
	}else{
		Logger << "不可能\n";
	}
	Logger << "　敵軍触接：";
	if(isYoursTrailer){
		Logger << "可能(";
		for(int i = 0; i < YoursShips; ++i){
			for(int j = 0; j < Yours[i].Slots; ++j){
				if((Yours[i].Weapons[j].Kind == "水偵") && (Rand(mt) <= 0.2)){
					if(YoursCond[i].NowAirs[j] > 0) YoursAttackPlus = AttackPlus[Yours[i].Weapons[j].Hit];
				}else if((Yours[i].Weapons[j].Kind == "艦偵") && (Rand(mt) <= 0.5)){
					if(YoursCond[i].NowAirs[j] > 0) YoursAttackPlus = AttackPlus[Yours[i].Weapons[j].Hit];
				}else if((Yours[i].Weapons[j].Kind == "艦攻") && (Rand(mt) <= 0.02)){
					if(YoursCond[i].NowAirs[j] > 0) YoursAttackPlus = AttackPlus[Yours[i].Weapons[j].Hit];
				}
				if(YoursAttackPlus != 0) break;
			}
			if(YoursAttackPlus != 0) break;
		}
		if(YoursAttackPlus != 0){
			Logger << "成功 +" << YoursAttackPlus << ")\n";
		}else{
			Logger << "失敗)\n";
		}
	}else{
		Logger << "不可能\n";
	}
	// 双方が戦闘機で艦載機を撃墜する
	//撃墜割合は一様分布にしたけど……これでいいのか？
	Logger << "○戦闘機による迎撃結果\n";
	int MineKilledAirsPer, YoursKilledAirsPer;
	switch(AntiAirResult){
		case AA_WORST:
			MineKilledAirsPer = Rand(mt) * 90;
			YoursKilledAirsPer = Rand(mt) * 10;
			break;
		case AA_BAD:
			MineKilledAirsPer = Rand(mt) * 80;
			YoursKilledAirsPer = Rand(mt) * 40;
			break;
		case AA_NORMAL:
			MineKilledAirsPer = Rand(mt) * 60;
			YoursKilledAirsPer = Rand(mt) * 60;
			break;
		case AA_GOOD:
			MineKilledAirsPer = Rand(mt) * 40;
			YoursKilledAirsPer = Rand(mt) * 80;
			break;
		case AA_BEST:
			MineKilledAirsPer = Rand(mt) * 10;
			YoursKilledAirsPer = Rand(mt) * 90;
			break;
	}
	Logger << "　自軍" << MineKilledAirsPer << "％\n　敵軍" << YoursKilledAirsPer << "％\n";
	for(int i = 0; i < MineShips; ++i){
		for(int j = 0; j < Mine[i].Slots; ++j){
			if((Mine[i].Weapons[j].Kind == "艦戦") || (Mine[i].Weapons[j].Kind == "艦攻")
			|| (Mine[i].Weapons[j].Kind == "艦爆") || (Mine[i].Weapons[j].Kind == "爆戦")
			|| (Mine[i].Weapons[j].Kind == "水爆")){
				MineCond[i].NowAirs[j] = MineKilledAirsPer * MineCond[i].NowAirs[j];
			}
		}
	}
	for(int i = 0; i < YoursShips; ++i){
		for(int j = 0; j < Yours[i].Slots; ++j){
			if((Yours[i].Weapons[j].Kind == "艦戦") || (Yours[i].Weapons[j].Kind == "艦攻")
			|| (Yours[i].Weapons[j].Kind == "艦爆") || (Yours[i].Weapons[j].Kind == "爆戦")
			|| (Yours[i].Weapons[j].Kind == "水爆")){
				YoursCond[i].NowAirs[j] = YoursKilledAirsPer * YoursCond[i].NowAirs[j];
			}
		}
	}
	// 双方が対空装備で艦載機を撃墜する
	//※面倒なので実装していません
	Logger << "○対空装備による迎撃結果(未実装)\n";
	while(1){
		// 生き残った艦載機による雷撃・爆撃
		Logger << "○攻撃結果\n";
		for(int i = 0; i < MineShips; ++i){
			if(YoursAlived.size() == 0) break;
			if(MineCond[i].NowHP == 0) continue;
			for(int j = 0; j < Mine[i].Slots; ++j){
				if(YoursAlived.size() == 0) break;
				if(MineCond[i].NowAirs[j] != 0){
					if(YoursAlived.size() != 0){
						if(Mine[i].Weapons[j].Kind == "艦攻"){
							int BaseAttack = (Mine[i].Weapons[j].Attack + Mine[i].Weapons[j].Torpedo) * sqrt(MineCond[i].NowAirs[j]) + 25;
							if(Rand(mt) < 0.5) BaseAttack = 1.5 * BaseAttack; else BaseAttack = 0.8 * BaseAttack;
							int Target = YoursAlived[Rand(mt) * YoursAlived.size()];
							AttackAction(Target, BaseAttack, Mine[i].Level, Yours, YoursAlived, YoursCond, MineForm, BattlePosition,
							             Mine[i].HP, MineCond[i].NowHP, 1.0, MineAttackPlus, 1.0, TURN_AIR);
							Logger << "　(自軍)" << Mine[i].Name << "の" << Mine[i].Weapons[j].Name << "が"
							       << Yours[Target].Name << "に攻撃！\n";
							Logger << "　　残り耐久：" << YoursCond[Target].NowHP << showDamage(YoursCond[Target].NowHP, Yours[Target].HP) << "\n";
						}
						if(Mine[i].Weapons[j].Kind == "艦爆"){
							int BaseAttack = (Mine[i].Weapons[j].Attack + Mine[i].Weapons[j].Torpedo) * sqrt(MineCond[i].NowAirs[j]) + 25;
							int Target = YoursAlived[Rand(mt) * YoursAlived.size()];
							AttackAction(Target, BaseAttack, Mine[i].Level, Yours, YoursAlived, YoursCond, MineForm, BattlePosition,
							             Mine[i].HP, MineCond[i].NowHP, 1.0, MineAttackPlus, 1.0, TURN_AIR);
							Logger << "　(自軍)" << Mine[i].Name << "の" << Mine[i].Weapons[j].Name << "が"
							       << Yours[Target].Name << "に攻撃！\n";
							Logger << "　　残り耐久：" << YoursCond[Target].NowHP << showDamage(YoursCond[Target].NowHP, Yours[Target].HP) << "\n";
						}
						if(Mine[i].Weapons[j].Kind == "爆戦"){
							int BaseAttack = (Mine[i].Weapons[j].Attack + Mine[i].Weapons[j].Torpedo) * sqrt(MineCond[i].NowAirs[j]) + 25;
							int Target = YoursAlived[Rand(mt) * YoursAlived.size()];
							AttackAction(Target, BaseAttack, Mine[i].Level, Yours, YoursAlived, YoursCond, MineForm, BattlePosition,
							             Mine[i].HP, MineCond[i].NowHP, 1.0, MineAttackPlus, 1.0, TURN_AIR);
							Logger << "　(自軍)" << Mine[i].Name << "の" << Mine[i].Weapons[j].Name << "が"
							       << Yours[Target].Name << "に攻撃！\n";
							Logger << "　　残り耐久：" << YoursCond[Target].NowHP << showDamage(YoursCond[Target].NowHP, Yours[Target].HP) << "\n";
						}
						if(Mine[i].Weapons[j].Kind == "水爆"){
							int BaseAttack = (Mine[i].Weapons[j].Attack + Mine[i].Weapons[j].Torpedo) * sqrt(MineCond[i].NowAirs[j]) + 25;
							int Target = YoursAlived[Rand(mt) * YoursAlived.size()];
							AttackAction(Target, BaseAttack, Mine[i].Level, Yours, YoursAlived, YoursCond, MineForm, BattlePosition,
							             Mine[i].HP, MineCond[i].NowHP, 1.0, MineAttackPlus, 1.0, TURN_AIR);
							Logger << "　(自軍)" << Mine[i].Name << "の" << Mine[i].Weapons[j].Name << "が"
							       << Yours[Target].Name << "に攻撃！\n";
							Logger << "　　残り耐久：" << YoursCond[Target].NowHP << showDamage(YoursCond[Target].NowHP, Yours[Target].HP) << "\n";
						}
					}
				}
			}
		}
		if(YoursAlived.size() == 0) break;
		for(int i = 0; i < YoursShips; ++i){
			if(MineAlived.size() == 0) break;
			if(YoursCond[i].NowHP == 0) continue;
			for(int j = 0; j < Yours[i].Slots; ++j){
				if(MineAlived.size() == 0) break;
				if(YoursCond[i].NowAirs[j] != 0){
					if(MineAlived.size() != 0){
						if(Yours[i].Weapons[j].Kind == "艦攻"){
							int BaseAttack = (Yours[i].Weapons[j].Attack + Yours[i].Weapons[j].Torpedo) * sqrt(YoursCond[i].NowAirs[j]) + 25;
							if(Rand(mt) < 0.5) BaseAttack = 1.5 * BaseAttack; else BaseAttack = 0.8 * BaseAttack;
							int Target = MineAlived[Rand(mt) * MineAlived.size()];
							AttackAction(Target, BaseAttack, Yours[i].Level, Mine, MineAlived, MineCond, YoursForm, BattlePosition,
							             Yours[i].HP, YoursCond[i].NowHP, 1.0, YoursAttackPlus, 1.0, TURN_AIR);
							Logger << "　(敵軍)" << Yours[i].Name << "の" << Yours[i].Weapons[j].Name << "が"
							       << Mine[Target].Name << "に攻撃！\n";
							Logger << "　　残り耐久：" << MineCond[Target].NowHP << showDamage(MineCond[Target].NowHP, Mine[Target].HP) << "\n";
						}
						if(Yours[i].Weapons[j].Kind == "艦爆"){
							int BaseAttack = (Yours[i].Weapons[j].Attack + Yours[i].Weapons[j].Torpedo) * sqrt(YoursCond[i].NowAirs[j]) + 25;
							int Target = MineAlived[Rand(mt) * MineAlived.size()];
							AttackAction(Target, BaseAttack, Yours[i].Level, Mine, MineAlived, MineCond, YoursForm, BattlePosition,
							             Yours[i].HP, YoursCond[i].NowHP, 1.0, YoursAttackPlus, 1.0, TURN_AIR);
							Logger << "　(敵軍)" << Yours[i].Name << "の" << Yours[i].Weapons[j].Name << "が"
							       << Mine[Target].Name << "に攻撃！\n";
							Logger << "　　残り耐久：" << MineCond[Target].NowHP << showDamage(MineCond[Target].NowHP, Mine[Target].HP) << "\n";
						}
						if(Yours[i].Weapons[j].Kind == "爆戦"){
							int BaseAttack = (Yours[i].Weapons[j].Attack + Yours[i].Weapons[j].Torpedo) * sqrt(YoursCond[i].NowAirs[j]) + 25;
							int Target = MineAlived[Rand(mt) * MineAlived.size()];
							AttackAction(Target, BaseAttack, Yours[i].Level, Mine, MineAlived, MineCond, YoursForm, BattlePosition,
							             Yours[i].HP, YoursCond[i].NowHP, 1.0, YoursAttackPlus, 1.0, TURN_AIR);
							Logger << "　(敵軍)" << Yours[i].Name << "の" << Yours[i].Weapons[j].Name << "が"
							       << Mine[Target].Name << "に攻撃！\n";
							Logger << "　　残り耐久：" << MineCond[Target].NowHP << showDamage(MineCond[Target].NowHP, Mine[Target].HP) << "\n";
						}
						if(Yours[i].Weapons[j].Kind == "水爆"){
							int BaseAttack = (Yours[i].Weapons[j].Attack + Yours[i].Weapons[j].Torpedo) * sqrt(YoursCond[i].NowAirs[j]) + 25;
							int Target = MineAlived[Rand(mt) * MineAlived.size()];
							AttackAction(Target, BaseAttack, Yours[i].Level, Mine, MineAlived, MineCond, YoursForm, BattlePosition,
							             Yours[i].HP, YoursCond[i].NowHP, 1.0, YoursAttackPlus, 1.0, TURN_AIR);
							Logger << "　(敵軍)" << Yours[i].Name << "の" << Yours[i].Weapons[j].Name << "が"
							       << Mine[Target].Name << "に攻撃！\n";
							Logger << "　　残り耐久：" << MineCond[Target].NowHP << showDamage(MineCond[Target].NowHP, Mine[Target].HP) << "\n";
						}
					}
				}
			}
		}
		if(MineAlived.size() == 0) break;

		/* 3. 開幕雷撃フェイズ */
		Logger << "【開幕雷撃フェイズ】\n";
		for(int i = 0; i < MineShips; ++i){
			if(YoursAlived.size() == 0) break;
			if(MineCond[i].NowHP == 0) continue;
			if(Mine[i].Kind & isFirstTorpedo){
				//Lv10以上の潜水艦ではない場合は甲標的が必要
				bool hasKohHyohteki = false;
				if(((Mine[i].Kind != SC_SS) && (Mine[i].Kind != SC_SSV)) ||
				(((Mine[i].Kind == SC_SS) || (Mine[i].Kind == SC_SSV)) && (Mine[i].Level < 10))){
					for(int j = 0; j < Mine[i].Slots; ++j){
						if(Mine[i].Weapons[j].Name.find("甲標的") != string::npos){
							hasKohHyohteki = true;
							break;
						}
					}
					if(!hasKohHyohteki) continue;
				}
				//開幕雷撃を行う(開幕なので素の雷装値は関係ない)
				int BaseAttack = Mine[i].Torpedo + 5;
				for(int j = 0; j < Mine[i].Slots; ++j){
					BaseAttack += Mine[i].Weapons[j].Torpedo;
				}
				int Target = YoursAlived[Rand(mt) * YoursAlived.size()];
				AttackAction(Target, BaseAttack, Mine[i].Level, Yours, YoursAlived, YoursCond, MineForm, BattlePosition,
							 Mine[i].HP, MineCond[i].NowHP, 1.0, MineAttackPlus, 1.0, TURN_TOR);
				Logger << "　(自軍)" << Mine[i].Name << "が" << Yours[Target].Name << "に攻撃！\n";
				Logger << "　　残り耐久：" << YoursCond[Target].NowHP << showDamage(YoursCond[Target].NowHP, Yours[Target].HP) << "\n";
			}
		}
		if(YoursAlived.size() == 0) break;
		for(int i = 0; i < YoursShips; ++i){
			if(MineAlived.size() == 0) break;
			if(YoursCond[i].NowHP == 0) continue;
			if(Yours[i].Kind & isFirstTorpedo){
				//Lv10以上の潜水艦ではない場合は甲標的が必要
				bool hasKohHyohteki = false;
				if(((Yours[i].Kind != SC_SS) && (Yours[i].Kind != SC_SSV)) ||
				(((Yours[i].Kind == SC_SS) || (Yours[i].Kind == SC_SSV)) && (Yours[i].Level < 10))){
					for(int j = 0; j < Yours[i].Slots; ++j){
						if(Yours[i].Weapons[j].Name.find("甲標的") != string::npos){
							hasKohHyohteki = true;
							break;
						}
					}
					if(!hasKohHyohteki) continue;
				}
				//開幕雷撃を行う(開幕なので素の雷装値は関係ない)
				int BaseAttack = Yours[i].Torpedo + 5;
				for(int j = 0; j < Yours[i].Slots; ++j){
					BaseAttack += Yours[i].Weapons[j].Torpedo;
				}
				int Target = MineAlived[Rand(mt) * MineAlived.size()];
				AttackAction(Target, BaseAttack, Yours[i].Level, Mine, MineAlived, MineCond, YoursForm, BattlePosition,
							 Yours[i].HP, YoursCond[i].NowHP, 1.0, YoursAttackPlus, 1.0, TURN_TOR);
				Logger << "　(敵軍)" << Yours[i].Name << "が" << Mine[Target].Name << "に攻撃！\n";
				Logger << "　　残り耐久：" << MineCond[Target].NowHP << showDamage(MineCond[Target].NowHP, Mine[Target].HP) << "\n";
			}
		}
		if(MineAlived.size() == 0) break;

		/* 4. 交戦形態フェイズ */
		Logger << "【交戦形態フェイズ】\n";
		Logger << "結果：";
		switch(BattlePosition){
			case BP_SAME:
				Logger << "同航戦\n";
				break;
			case BP_DIFF:
				Logger << "反航戦\n";
				break;
			case BP_T_Plus:
				Logger << "T字戦(有利)\n";
				break;
			case BP_T_Minus:
				Logger << "T字戦(不利)\n";
				break;
		}

		/* 5. 砲撃戦フェイズ */
		Logger << "【砲撃戦フェイズ】\n";
		if(YoursAlived.size() == 0) break;
		if(MineAlived.size() == 0) break;
		// 一周目：射程の長い順に決定
		//先にシャッフルしてから安定なソートを掛けることで、
		//「同一射程ならランダム」を再現しているつもり
		for(int i = 0; i < MineAlived.size() - 1; ++i){
			int temp = MineAlived[i];
			int j = Rand(mt) * MineAlived.size();
			MineAlived[i] = MineAlived[j];
			MineAlived[j] = temp;
		}
		for(int i = 0; i < MineAlived.size() - 1; ++i){
			for(int j = i + 1; j < MineAlived.size(); ++j){
				REACH MineReachMaxI = Mine[MineAlived[i]].Reach;
				for(int k = 0; k < Mine[MineAlived[i]].Slots; ++k){
					if(MineReachMaxI < Mine[MineAlived[i]].Weapons[k].Reach)
						MineReachMaxI = Mine[MineAlived[i]].Weapons[k].Reach;
				}
				REACH MineReachMaxJ = Mine[MineAlived[j]].Reach;
				for(int k = 0; k < Mine[MineAlived[j]].Slots; ++k){
					if(MineReachMaxJ < Mine[MineAlived[j]].Weapons[k].Reach)
						MineReachMaxJ = Mine[MineAlived[j]].Weapons[k].Reach;
				}
				if(MineReachMaxI < MineReachMaxJ){
					int temp = MineAlived[i];
					MineAlived[i] = MineAlived[j];
					MineAlived[j] = temp;
				}
			}
		}
		for(int i = 0; i < YoursAlived.size() - 1; ++i){
			int temp = YoursAlived[i];
			int j = Rand(mt) * YoursAlived.size();
			YoursAlived[i] = YoursAlived[j];
			YoursAlived[j] = YoursAlived[i];
		}
		for(int i = 0; i < YoursAlived.size() - 1; ++i){
			for(int j = i + 1; j < YoursAlived.size(); ++j){
				REACH YoursReachMaxI = Yours[YoursAlived[i]].Reach;
				for(int k = 0; k < Yours[YoursAlived[i]].Slots; ++k){
					if(YoursReachMaxI < Yours[YoursAlived[i]].Weapons[k].Reach)
						YoursReachMaxI = Yours[YoursAlived[i]].Weapons[k].Reach;
				}
				REACH YoursReachMaxJ = Yours[YoursAlived[j]].Reach;
				for(int k = 0; k < Yours[YoursAlived[j]].Slots; ++k){
					if(YoursReachMaxJ < Yours[YoursAlived[j]].Weapons[k].Reach)
						YoursReachMaxJ = Yours[YoursAlived[j]].Weapons[k].Reach;
				}
				if(YoursReachMaxI < YoursReachMaxJ){
					int temp = YoursAlived[i];
					YoursAlived[i] = YoursAlived[j];
					YoursAlived[j] = temp;
				}
			}
		}
		vector<int> MineAlived_ = MineAlived, YoursAlived_ = YoursAlived;	//生存艦のリストをバックアップ
		for(int i = 0; i < MaxKanmusu; ++i){
			//自分が攻撃
			if(i < MineAlived_.size()){
				vector<int>::iterator cIter = find(MineAlived.begin(), MineAlived.end(), MineAlived_[i]);
				if(cIter != MineAlived.end()){
					int Move = MineAlived_[i];
					int Target = YoursAlived[Rand(mt) * YoursAlived.size()];
					int BaseAttack = 0;
					//(敵に潜水艦がいた場合は優先的に攻撃)
					bool isSubAttack = false;
					vector<int> SubList;
					if(Mine[Move].Kind & isAntiSub){
						for(int j = 0; j < YoursAlived.size(); ++j){
							if((Yours[YoursAlived[j]].Kind == SC_SS)
							|| (Yours[YoursAlived[j]].Kind == SC_SSV)){
								SubList.push_back(YoursAlived[j]);
								isSubAttack = true;
							}
						}
					}
					if(isSubAttack){
						Target = SubList[Rand(mt) * SubList.size()];
						BaseAttack = Mine[Move].AntiSub / 5;
						bool hasAntiSubBomb = false;
						bool hasAntiSubSonar = false;
						for(int j = 0; j < Mine[Move].Slots; ++j){
							BaseAttack += Mine[Move].Weapons[j].AntiSub * 2;
							if(Mine[Move].Weapons[j].Kind == "爆雷") hasAntiSubBomb = true;
							if(Mine[Move].Weapons[j].Kind == "ソナー") hasAntiSubSonar = true;
						}
						if(hasAntiSubBomb & hasAntiSubSonar){
							//セット運用
							BaseAttack = 1.15 * (BaseAttack + 25);
						}else if(hasAntiSubBomb | hasAntiSubSonar){
							//片方のみ
							BaseAttack =BaseAttack + 25;
						}else{
							//艦載機による攻撃
							BaseAttack = BaseAttack + 10;
						}
					}else{
						//(通常の攻撃)
						if(Mine[Move].Kind & isAirs3){
							//空母系
							if(Mine[Move].HP * 0.25 >= MineCond[Move].NowHP) continue;
							int AllAttack = Mine[Move].Attack;
							int AllTorpedo = 0;
							int AllBomb = 0;
							for(int j = 0; j < Mine[Move].Slots; ++j){
								AllAttack += Mine[Move].Weapons[j].Attack;
								AllTorpedo += Mine[Move].Weapons[j].Torpedo;
								AllBomb += Mine[Move].Weapons[j].Bomb;
							}
							if((AllTorpedo == 0) && (AllBomb == 0)) continue;
							BaseAttack = (AllAttack + AllTorpedo) * 1.5 + AllBomb * 2 + 55;
						}else{
							//空母系以外
							BaseAttack = Mine[Move].Attack + 5;
							for(int j = 0; j < Mine[Move].Slots; ++j){
								BaseAttack += Mine[Move].Weapons[j].Attack;
							}
						}
					}
					AttackAction(Target, BaseAttack, Mine[Move].Level, Yours, YoursAlived, YoursCond, MineForm, BattlePosition,
								 Mine[Move].HP, MineCond[Move].NowHP, 1.0, MineAttackPlus, 1.0, TURN_NOON);
					Logger << "　(自軍)" << Mine[Move].Name << "が" << Yours[Target].Name << "に攻撃！\n";
					Logger << "　　残り耐久：" << YoursCond[Target].NowHP << showDamage(YoursCond[Target].NowHP, Yours[Target].HP) << "\n";
					if(YoursAlived.size() == 0) break;
				}
				if(YoursAlived.size() == 0) break;
			}
			if(YoursAlived.size() == 0) break;
			//相手が攻撃
			if(i < YoursAlived_.size()){
				vector<int>::iterator cIter = find(YoursAlived.begin(), YoursAlived.end(), YoursAlived_[i]);
				if(cIter != YoursAlived.end()){
					int Move = YoursAlived_[i];
					int Target = MineAlived[Rand(mt) * MineAlived.size()];
					int BaseAttack = 0;
					//(敵に潜水艦がいた場合は優先的に攻撃)
					bool isSubAttack = false;
					vector<int> SubList;
					if(Yours[Move].Kind & isAntiSub){
						for(int j = 0; j < MineAlived.size(); ++j){
							if((Mine[MineAlived[j]].Kind == SC_SS)
							|| (Mine[MineAlived[j]].Kind == SC_SSV)){
								SubList.push_back(MineAlived[j]);
								isSubAttack = true;
							}
						}
					}
					if(isSubAttack){
						Target = SubList[Rand(mt) * SubList.size()];
						BaseAttack = Yours[Move].AntiSub / 5;
						bool hasAntiSubBomb = false;
						bool hasAntiSubSonar = false;
						for(int j = 0; j < Yours[Move].Slots; ++j){
							BaseAttack += Yours[Move].Weapons[j].AntiSub * 2;
							if(Yours[Move].Weapons[j].Kind == "爆雷") hasAntiSubBomb = true;
							if(Yours[Move].Weapons[j].Kind == "ソナー") hasAntiSubSonar = true;
						}
						if(hasAntiSubBomb & hasAntiSubSonar){
							//セット運用
							BaseAttack = 1.15 * (BaseAttack + 25);
						}else if(hasAntiSubBomb | hasAntiSubSonar){
							//片方のみ
							BaseAttack =BaseAttack + 25;
						}else{
							//艦載機による攻撃
							BaseAttack = BaseAttack + 10;
						}
					}else{
						//(通常の攻撃)
						if(Yours[Move].Kind & isAirs3){
							//空母系
							if(Yours[Move].HP * 0.25 >= YoursCond[Move].NowHP) continue;
							int AllAttack = Yours[Move].Attack;
							int AllTorpedo = 0;
							int AllBomb = 0;
							for(int j = 0; j < Yours[Move].Slots; ++j){
								AllAttack += Yours[Move].Weapons[j].Attack;
								AllTorpedo += Yours[Move].Weapons[j].Torpedo;
								AllBomb += Yours[Move].Weapons[j].Bomb;
							}
							if((AllTorpedo == 0) && (AllBomb == 0)) continue;
							BaseAttack = (AllAttack + AllTorpedo) * 1.5 + AllBomb * 2 + 55;
						}else{
							//空母系以外
							BaseAttack = Yours[Move].Attack + 5;
							for(int j = 0; j < Yours[Move].Slots; ++j){
								BaseAttack += Yours[Move].Weapons[j].Attack;
							}
						}
					}
					AttackAction(Target, BaseAttack, Yours[Move].Level, Mine, MineAlived, MineCond, YoursForm, BattlePosition,
								 Yours[Move].HP, YoursCond[Move].NowHP, 1.0, YoursAttackPlus, 1.0, TURN_NOON);
					Logger << "　(敵軍)" << Yours[Move].Name << "が" << Mine[Target].Name << "に攻撃！\n";
					Logger << "　　残り耐久：" << MineCond[Target].NowHP << showDamage(MineCond[Target].NowHP, Mine[Target].HP) << "\n";
					if(MineAlived.size() == 0) break;
				}
				if(MineAlived.size() == 0) break;
			}
			if(MineAlived.size() == 0) break;
		}
		if((YoursAlived.size() == 0) || (MineAlived.size() == 0)) break;
		// 二周目：上から順に攻撃(戦艦・航戦が存在する場合のみ)
		bool hasBB = false;
		for(int i = 0; i < MineShips; ++i){
			if(Mine[i].Kind & isBB){
				hasBB = true;
				break;
			}
		}
		for(int i = 0; i < YoursShips; ++i){
			if(Yours[i].Kind & isBB){
				hasBB = true;
				break;
			}
		}
		MineAlived.clear(); YoursAlived.clear();
		for(int i = 0; i < MineShips; ++i){
			if(MineCond[i].NowHP != 0){
				MineAlived.push_back(i);
			}
		}
		for(int i = 0; i < YoursShips; ++i){
			if(YoursCond[i].NowHP != 0){
				YoursAlived.push_back(i);
			}
		}
		if(hasBB){
			MineAlived_ = MineAlived, YoursAlived_ = YoursAlived;
			for(int i = 0; i < MaxKanmusu; ++i){
				//自分が攻撃
				if(i < MineAlived_.size()){
					vector<int>::iterator cIter = find(MineAlived.begin(), MineAlived.end(), MineAlived_[i]);
					if(cIter != MineAlived.end()){
						int Move = MineAlived_[i];
						int Target = YoursAlived[Rand(mt) * YoursAlived.size()];
						int BaseAttack = 0;
						//(敵に潜水艦がいた場合は優先的に攻撃)
						bool isSubAttack = false;
						vector<int> SubList;
						if(Mine[Move].Kind & isAntiSub){
							for(int j = 0; j < YoursAlived.size(); ++j){
								if((Yours[YoursAlived[j]].Kind == SC_SS)
								|| (Yours[YoursAlived[j]].Kind == SC_SSV)){
									SubList.push_back(YoursAlived[j]);
									isSubAttack = true;
								}
							}
						}
						if(isSubAttack){
							Target = SubList[Rand(mt) * SubList.size()];
							BaseAttack = Mine[Move].AntiSub / 5;
							bool hasAntiSubBomb = false;
							bool hasAntiSubSonar = false;
							for(int j = 0; j < Mine[Move].Slots; ++j){
								BaseAttack += Mine[Move].Weapons[j].AntiSub * 2;
								if(Mine[Move].Weapons[j].Kind == "爆雷") hasAntiSubBomb = true;
								if(Mine[Move].Weapons[j].Kind == "ソナー") hasAntiSubSonar = true;
							}
							if(hasAntiSubBomb & hasAntiSubSonar){
								//セット運用
								BaseAttack = 1.15 * (BaseAttack + 25);
							}else if(hasAntiSubBomb | hasAntiSubSonar){
								//片方のみ
								BaseAttack =BaseAttack + 25;
							}else{
								//艦載機による攻撃
								BaseAttack = BaseAttack + 10;
							}
						}else{
							//(通常の攻撃)
							if(Mine[Move].Kind & isAirs3){
								//空母系
								if(Mine[Move].HP * 0.5 >= MineCond[Move].NowHP) continue;
								int AllAttack = Mine[Move].Attack;
								int AllTorpedo = 0;
								int AllBomb = 0;
								for(int j = 0; j < Mine[Move].Slots; ++j){
									AllAttack += Mine[Move].Weapons[j].Attack;
									AllTorpedo += Mine[Move].Weapons[j].Torpedo;
									AllBomb += Mine[Move].Weapons[j].Bomb;
								}
								if((AllTorpedo == 0) && (AllBomb == 0)) continue;
								BaseAttack = (AllAttack + AllTorpedo) * 1.5 + AllBomb * 2 + 55;
							}else{
								//空母系以外
								BaseAttack = Mine[Move].Attack + 5;
								for(int j = 0; j < Mine[Move].Slots; ++j){
									BaseAttack += Mine[Move].Weapons[j].Attack;
								}
							}
						}
						AttackAction(Target, BaseAttack, Mine[Move].Level, Yours, YoursAlived, YoursCond, MineForm, BattlePosition,
									 Mine[Move].HP, MineCond[Move].NowHP, 1.0, MineAttackPlus, 1.0, TURN_NOON);
						Logger << "　(自軍)" << Mine[Move].Name << "が" << Yours[Target].Name << "に攻撃！\n";
						Logger << "　　残り耐久：" << YoursCond[Target].NowHP << showDamage(YoursCond[Target].NowHP, Yours[Target].HP) << "\n";
						if(YoursAlived.size() == 0) break;
					}
					if(YoursAlived.size() == 0) break;
				}
				if(YoursAlived.size() == 0) break;
				//相手が攻撃
				if(i < YoursAlived_.size()){
					vector<int>::iterator cIter = find(YoursAlived.begin(), YoursAlived.end(), YoursAlived_[i]);
					if(cIter != YoursAlived.end()){
						int Move = YoursAlived_[i];
						int Target = MineAlived[Rand(mt) * MineAlived.size()];
						int BaseAttack = 0;
						//(敵に潜水艦がいた場合は優先的に攻撃)
						bool isSubAttack = false;
						vector<int> SubList;
						if(Yours[Move].Kind & isAntiSub){
							for(int j = 0; j < MineAlived.size(); ++j){
								if((Mine[MineAlived[j]].Kind == SC_SS)
								|| (Mine[MineAlived[j]].Kind == SC_SSV)){
									SubList.push_back(MineAlived[j]);
									isSubAttack = true;
								}
							}
						}
						if(isSubAttack){
							Target = SubList[Rand(mt) * SubList.size()];
							BaseAttack = Yours[Move].AntiSub / 5;
							bool hasAntiSubBomb = false;
							bool hasAntiSubSonar = false;
							for(int j = 0; j < Yours[Move].Slots; ++j){
								BaseAttack += Yours[Move].Weapons[j].AntiSub * 2;
								if(Yours[Move].Weapons[j].Kind == "爆雷") hasAntiSubBomb = true;
								if(Yours[Move].Weapons[j].Kind == "ソナー") hasAntiSubSonar = true;
							}
							if(hasAntiSubBomb & hasAntiSubSonar){
								//セット運用
								BaseAttack = 1.15 * (BaseAttack + 25);
							}else if(hasAntiSubBomb | hasAntiSubSonar){
								//片方のみ
								BaseAttack =BaseAttack + 25;
							}else{
								//艦載機による攻撃
								BaseAttack = BaseAttack + 10;
							}
						}else{
							//(通常の攻撃)
							if(Yours[Move].Kind & isAirs3){
								//空母系
								if(Yours[Move].HP * 0.5 >= YoursCond[Move].NowHP) continue;
								int AllAttack = Yours[Move].Attack;
								int AllTorpedo = 0;
								int AllBomb = 0;
								for(int j = 0; j < Yours[Move].Slots; ++j){
									AllAttack += Yours[Move].Weapons[j].Attack;
									AllTorpedo += Yours[Move].Weapons[j].Torpedo;
									AllBomb += Yours[Move].Weapons[j].Bomb;
								}
								if((AllTorpedo == 0) && (AllBomb == 0)) continue;
								BaseAttack = (AllAttack + AllTorpedo) * 1.5 + AllBomb * 2 + 55;
							}else{
								//空母系以外
								BaseAttack = Yours[Move].Attack + 5;
								for(int j = 0; j < Yours[Move].Slots; ++j){
									BaseAttack += Yours[Move].Weapons[j].Attack;
								}
							}
						}
						AttackAction(Target, BaseAttack, Yours[Move].Level, Mine, MineAlived, MineCond, YoursForm, BattlePosition,
									 Yours[Move].HP, YoursCond[Move].NowHP, 1.0, YoursAttackPlus, 1.0, TURN_NOON);
						Logger << "　(敵軍)" << Yours[Move].Name << "が" << Mine[Target].Name << "に攻撃！\n";
						Logger << "　　残り耐久：" << MineCond[Target].NowHP << showDamage(MineCond[Target].NowHP, Mine[Target].HP) << "\n";
						if(MineAlived.size() == 0) break;
					}
					if(MineAlived.size() == 0) break;
				}
				if(MineAlived.size() == 0) break;
			}
			if((YoursAlived.size() == 0) || (MineAlived.size() == 0)) break;
		}

		/* 6. 雷撃戦フェイズ */
		Logger << "【雷撃戦フェイズ】\n";
		for(int i = 0; i < MineShips; ++i){
			if(MineCond[i].NowHP == 0) continue;
			if(Mine[i].Kind & isTorpedo){
				//雷撃を行う(素の雷装値が0でない場合のみ攻撃する)
				if(Mine[i].Torpedo == 0) continue;
				if(Mine[i].HP * 0.5 >= MineCond[i].NowHP) continue;
				int BaseAttack = Mine[i].Torpedo + 5;
				for(int j = 0; j < Mine[i].Slots; ++j){
					BaseAttack += Mine[i].Weapons[j].Torpedo;
				}
				vector<int> YoursAlivedWithoutSS;//潜水艦系は攻撃できないので避ける
				for(int j = 0; j < YoursAlived.size(); ++j){
					if((Yours[YoursAlived[j]].Kind != SC_SS) && (Yours[YoursAlived[j]].Kind != SC_SSV)){
						YoursAlivedWithoutSS.push_back(YoursAlived[j]);
					}
				}
				int Target = YoursAlivedWithoutSS[Rand(mt) * YoursAlivedWithoutSS.size()];
				AttackAction(Target, BaseAttack, Mine[i].Level, Yours, YoursAlived, YoursCond, MineForm, BattlePosition,
							 Mine[i].HP, MineCond[i].NowHP, 1.0, MineAttackPlus, 1.0, TURN_TOR);
				Logger << "　(自軍)" << Mine[i].Name << "が" << Yours[Target].Name << "に攻撃！\n";
				Logger << "　　残り耐久：" << YoursCond[Target].NowHP << showDamage(YoursCond[Target].NowHP, Yours[Target].HP) << "\n";
				if(YoursAlived.size() == 0) break;
			}
		}
		if(YoursAlived.size() == 0) break;
		for(int i = 0; i < YoursShips; ++i){
			if(YoursCond[i].NowHP == 0) continue;
			if(Yours[i].Kind & isTorpedo){
				//雷撃を行う(素の雷装値が0でない場合のみ攻撃する)
				if(Yours[i].Torpedo == 0) continue;
				if(Yours[i].HP * 0.5 >= YoursCond[i].NowHP) continue;
				int BaseAttack = Yours[i].Torpedo + 5;
				for(int j = 0; j < Yours[i].Slots; ++j){
					BaseAttack += Yours[i].Weapons[j].Torpedo;
				}
				vector<int> MineAlivedWithoutSS;//潜水艦系は攻撃できないので避ける
				for(int j = 0; j < MineAlived.size(); ++j){
					if((Mine[MineAlived[j]].Kind != SC_SS) && (Mine[MineAlived[j]].Kind != SC_SSV)){
						MineAlivedWithoutSS.push_back(MineAlived[j]);
					}
				}
				int Target = MineAlivedWithoutSS[Rand(mt) * MineAlivedWithoutSS.size()];
				AttackAction(Target, BaseAttack, Yours[i].Level, Mine, MineAlived, MineCond, YoursForm, BattlePosition,
							 Yours[i].HP, YoursCond[i].NowHP, 1.0, YoursAttackPlus, 1.0, TURN_TOR);
				Logger << "　(敵軍)" << Yours[i].Name << "が" << Mine[Target].Name << "に攻撃！\n";
				Logger << "　　残り耐久：" << MineCond[Target].NowHP << showDamage(MineCond[Target].NowHP, Mine[Target].HP) << "\n";
				if(MineAlived.size() == 0) break;
			}
		}
		if(MineAlived.size() == 0) break;

		/* 7. 夜戦フェイズ */
		Logger << "【夜戦フェイズ】\n";
		MineAlived_ = MineAlived, YoursAlived_ = YoursAlived;
		for(int i = 0; i < MaxKanmusu; ++i){
			//自分が攻撃
			if(i < MineAlived_.size()){
				vector<int>::iterator cIter = find(MineAlived.begin(), MineAlived.end(), MineAlived_[i]);
				if(cIter != MineAlived.end()){
					int Move = MineAlived_[i];
					if(Mine[Move].HP * 0.25 >= MineCond[Move].NowHP) continue;
					if(Mine[Move].Kind & isAirs3) continue;
					int Target = YoursAlived[Rand(mt) * YoursAlived.size()];
					int BaseAttack = 0;
					//(敵に潜水艦がいた場合は優先的に攻撃)
					bool isSubAttack = false;
					vector<int> SubList;
					if((Mine[Move].Kind == SC_DD) || (Mine[Move].Kind == SC_CL) || (Mine[Move].Kind == SC_CLT)){
						for(int j = 0; j < YoursAlived.size(); ++j){
							if((Yours[YoursAlived[j]].Kind == SC_SS)
							|| (Yours[YoursAlived[j]].Kind == SC_SSV)){
								SubList.push_back(YoursAlived[j]);
								isSubAttack = true;
							}
						}
					}
					if(isSubAttack){
						Target = SubList[Rand(mt) * SubList.size()];
						BaseAttack = 0;	//強制的にカスダメとする(暫定的な処理)
						AttackAction(Target, BaseAttack, Mine[Move].Level, Yours, YoursAlived, YoursCond, MineForm, BattlePosition,
									 Mine[Move].HP, MineCond[Move].NowHP, 1.0, MineAttackPlus, 1.0, TURN_NIGHT);
						Logger << "　(自軍)" << Mine[Move].Name << "が" << Yours[Target].Name << "に攻撃！\n";
						Logger << "　　残り耐久：" << YoursCond[Target].NowHP << showDamage(YoursCond[Target].NowHP, Yours[Target].HP) << "\n";
						if(YoursAlived.size() == 0) break;
					}else{
						BaseAttack = Mine[Move].Attack + Mine[Move].Torpedo;
						int GunCount = 0, SubGunCount = 0, TorCount = 0;
						for(int j = 0; j < Mine[Move].Slots; ++j){
							BaseAttack += Mine[Move].Weapons[j].Attack;
							BaseAttack += Mine[Move].Weapons[j].Torpedo;
							if(Mine[Move].Weapons[j].Kind == "主砲"){
								++GunCount;
							}else if(Mine[Move].Weapons[j].Kind == "副砲"){
								++SubGunCount;
							}else if(Mine[Move].Weapons[j].Kind == "魚雷"){
								++TorCount;
							}
						}
						// 夜間特殊攻撃に関する処理
						//カットイン確率を計算
						int CutinPer = 0.85 * Mine[Move].Luck + 15;
						if(Move != 0) CutinPer += 15;
						if(Mine[Move].HP * 0.25 >= MineCond[Move].NowHP){
							CutinPer += 20;
						}else if(Mine[Move].HP * 0.5 >= MineCond[Move].NowHP){
							CutinPer += 10;
						}
						for(int k = 0; k < MineShips; ++k){
							for(int j = 0; j < Mine[k].Slots; ++j){
								if((Mine[k].Weapons[j].Name == "探照灯")
								|| (Mine[k].Weapons[j].Name == "照明弾")){
									CutinPer += 5;
								}
							}
						}
						for(int k = 0; k < YoursShips; ++k){
							for(int j = 0; j < Yours[k].Slots; ++j){
								if((Yours[k].Weapons[j].Name == "探照灯")
								|| (Yours[k].Weapons[j].Name == "照明弾")){
									CutinPer -= 10;
								}
							}
						}
						if(TorCount >= 2){	//カットイン判定
							if(Rand(mt) * 100 < CutinPer){
								AttackAction(Target, BaseAttack, Mine[Move].Level, Yours, YoursAlived, YoursCond, MineForm, BattlePosition,
											 Mine[Move].HP, MineCond[Move].NowHP, 1.5, MineAttackPlus, 1.0, TURN_NIGHT);
								AttackAction(Target, BaseAttack, Mine[Move].Level, Yours, YoursAlived, YoursCond, MineForm, BattlePosition,
											 Mine[Move].HP, MineCond[Move].NowHP, 1.5, MineAttackPlus, 1.0, TURN_NIGHT);
								Logger << "　(自軍)" << Mine[Move].Name << "が" << Yours[Target].Name << "にカットイン攻撃！\n";
								Logger << "　　残り耐久：" << YoursCond[Target].NowHP << showDamage(YoursCond[Target].NowHP, Yours[Target].HP) << "\n";
							}else{
								AttackAction(Target, BaseAttack, Mine[Move].Level, Yours, YoursAlived, YoursCond, MineForm, BattlePosition,
											 Mine[Move].HP, MineCond[Move].NowHP, 1.0, MineAttackPlus, 1.0, TURN_NIGHT);
								Logger << "　(自軍)" << Mine[Move].Name << "が" << Yours[Target].Name << "に攻撃！\n";
								Logger << "　　残り耐久：" << YoursCond[Target].NowHP << showDamage(YoursCond[Target].NowHP, Yours[Target].HP) << "\n";
							}
						}else if(GunCount >= 3){
							if(Rand(mt) * 100 < CutinPer){
								AttackAction(Target, BaseAttack, Mine[Move].Level, Yours, YoursAlived, YoursCond, MineForm, BattlePosition,
											 Mine[Move].HP, MineCond[Move].NowHP, 2.0, MineAttackPlus, 1.0, TURN_NIGHT);
								Logger << "　(自軍)" << Mine[Move].Name << "が" << Yours[Target].Name << "にカットイン攻撃！\n";
								Logger << "　　残り耐久：" << YoursCond[Target].NowHP << showDamage(YoursCond[Target].NowHP, Yours[Target].HP) << "\n";
							}else{
								AttackAction(Target, BaseAttack, Mine[Move].Level, Yours, YoursAlived, YoursCond, MineForm, BattlePosition,
											 Mine[Move].HP, MineCond[Move].NowHP, 1.0, MineAttackPlus, 1.0, TURN_NIGHT);
								Logger << "　(自軍)" << Mine[Move].Name << "が" << Yours[Target].Name << "に攻撃！\n";
								Logger << "　　残り耐久：" << YoursCond[Target].NowHP << showDamage(YoursCond[Target].NowHP, Yours[Target].HP) << "\n";
							}
						}else if((GunCount == 2) && (SubGunCount >= 1)){
							if(Rand(mt) * 100 < CutinPer){
								AttackAction(Target, BaseAttack, Mine[Move].Level, Yours, YoursAlived, YoursCond, MineForm, BattlePosition,
											 Mine[Move].HP, MineCond[Move].NowHP, 1.75, MineAttackPlus, 1.0, TURN_NIGHT);
								Logger << "　(自軍)" << Mine[Move].Name << "が" << Yours[Target].Name << "にカットイン攻撃！\n";
								Logger << "　　残り耐久：" << YoursCond[Target].NowHP << showDamage(YoursCond[Target].NowHP, Yours[Target].HP) << "\n";
							}else{
								AttackAction(Target, BaseAttack, Mine[Move].Level, Yours, YoursAlived, YoursCond, MineForm, BattlePosition,
											 Mine[Move].HP, MineCond[Move].NowHP, 1.0, MineAttackPlus, 1.0, TURN_NIGHT);
								Logger << "　(自軍)" << Mine[Move].Name << "が" << Yours[Target].Name << "に攻撃！\n";
								Logger << "　　残り耐久：" << YoursCond[Target].NowHP << showDamage(YoursCond[Target].NowHP, Yours[Target].HP) << "\n";
							}
						}else if(((GunCount == 1) || (GunCount == 2)) && (TorCount == 1)){
							if(Rand(mt) * 100 < CutinPer){
								AttackAction(Target, BaseAttack, Mine[Move].Level, Yours, YoursAlived, YoursCond, MineForm, BattlePosition,
											 Mine[Move].HP, MineCond[Move].NowHP, 1.3, MineAttackPlus, 1.0, TURN_NIGHT);
								AttackAction(Target, BaseAttack, Mine[Move].Level, Yours, YoursAlived, YoursCond, MineForm, BattlePosition,
											 Mine[Move].HP, MineCond[Move].NowHP, 1.3, MineAttackPlus, 1.0, TURN_NIGHT);
								Logger << "　(自軍)" << Mine[Move].Name << "が" << Yours[Target].Name << "にカットイン攻撃！\n";
								Logger << "　　残り耐久：" << YoursCond[Target].NowHP << showDamage(YoursCond[Target].NowHP, Yours[Target].HP) << "\n";
							}else{
								AttackAction(Target, BaseAttack, Mine[Move].Level, Yours, YoursAlived, YoursCond, MineForm, BattlePosition,
											 Mine[Move].HP, MineCond[Move].NowHP, 1.0, MineAttackPlus, 1.0, TURN_NIGHT);
								Logger << "　(自軍)" << Mine[Move].Name << "が" << Yours[Target].Name << "に攻撃！\n";
								Logger << "　　残り耐久：" << YoursCond[Target].NowHP << showDamage(YoursCond[Target].NowHP, Yours[Target].HP) << "\n";
							}
						}else if((GunCount == 2) && (SubGunCount == 0) && (TorCount == 0)){	//連撃判定
							AttackAction(Target, BaseAttack, Mine[Move].Level, Yours, YoursAlived, YoursCond, MineForm, BattlePosition,
										 Mine[Move].HP, MineCond[Move].NowHP, 1.2, MineAttackPlus, 1.0, TURN_NIGHT);
							AttackAction(Target, BaseAttack, Mine[Move].Level, Yours, YoursAlived, YoursCond, MineForm, BattlePosition,
										 Mine[Move].HP, MineCond[Move].NowHP, 1.2, MineAttackPlus, 1.0, TURN_NIGHT);
							Logger << "　(自軍)" << Mine[Move].Name << "が" << Yours[Target].Name << "に連撃！\n";
							Logger << "　　残り耐久：" << YoursCond[Target].NowHP << showDamage(YoursCond[Target].NowHP, Yours[Target].HP) << "\n";
						}else if((GunCount == 1) && (SubGunCount >= 1) && (TorCount == 0)){
							AttackAction(Target, BaseAttack, Mine[Move].Level, Yours, YoursAlived, YoursCond, MineForm, BattlePosition,
										 Mine[Move].HP, MineCond[Move].NowHP, 1.2, MineAttackPlus, 1.0, TURN_NIGHT);
							AttackAction(Target, BaseAttack, Mine[Move].Level, Yours, YoursAlived, YoursCond, MineForm, BattlePosition,
										 Mine[Move].HP, MineCond[Move].NowHP, 1.2, MineAttackPlus, 1.0, TURN_NIGHT);
							Logger << "　(自軍)" << Mine[Move].Name << "が" << Yours[Target].Name << "に連撃！\n";
							Logger << "　　残り耐久：" << YoursCond[Target].NowHP << showDamage(YoursCond[Target].NowHP, Yours[Target].HP) << "\n";
						}else if((GunCount == 0) && (SubGunCount >= 2) && (TorCount <= 1)){
							AttackAction(Target, BaseAttack, Mine[Move].Level, Yours, YoursAlived, YoursCond, MineForm, BattlePosition,
										 Mine[Move].HP, MineCond[Move].NowHP, 1.2, MineAttackPlus, 1.0, TURN_NIGHT);
							AttackAction(Target, BaseAttack, Mine[Move].Level, Yours, YoursAlived, YoursCond, MineForm, BattlePosition,
										 Mine[Move].HP, MineCond[Move].NowHP, 1.2, MineAttackPlus, 1.0, TURN_NIGHT);
							Logger << "　(自軍)" << Mine[Move].Name << "が" << Yours[Target].Name << "に連撃！\n";
							Logger << "　　残り耐久：" << YoursCond[Target].NowHP << showDamage(YoursCond[Target].NowHP, Yours[Target].HP) << "\n";
						}else{	//その他
							AttackAction(Target, BaseAttack, Mine[Move].Level, Yours, YoursAlived, YoursCond, MineForm, BattlePosition,
										 Mine[Move].HP, MineCond[Move].NowHP, 1.0, MineAttackPlus, 1.0, TURN_NIGHT);
							Logger << "　(自軍)" << Mine[Move].Name << "が" << Yours[Target].Name << "に攻撃！\n";
							Logger << "　　残り耐久：" << YoursCond[Target].NowHP << showDamage(YoursCond[Target].NowHP, Yours[Target].HP) << "\n";
						}
						if(YoursAlived.size() == 0) break;
					}
				}
				if(YoursAlived.size() == 0) break;
			}
			if(YoursAlived.size() == 0) break;
			//相手が攻撃
			if(i < YoursAlived_.size()){
				vector<int>::iterator cIter = find(YoursAlived.begin(), YoursAlived.end(), YoursAlived_[i]);
				if(cIter != YoursAlived.end()){
					int Move = YoursAlived_[i];
					if(Yours[Move].HP * 0.25 >= YoursCond[Move].NowHP) continue;
					if(Yours[Move].Kind & isAirs3) continue;
					int Target = MineAlived[Rand(mt) * MineAlived.size()];
					int BaseAttack = 0;
					//(敵に潜水艦がいた場合は優先的に攻撃)
					bool isSubAttack = false;
					vector<int> SubList;
					if((Yours[Move].Kind == SC_DD) || (Yours[Move].Kind == SC_CL) || (Yours[Move].Kind == SC_CLT)){
						for(int j = 0; j < MineAlived.size(); ++j){
							if((Mine[MineAlived[j]].Kind == SC_SS)
							|| (Mine[MineAlived[j]].Kind == SC_SSV)){
								SubList.push_back(MineAlived[j]);
								isSubAttack = true;
							}
						}
					}
					if(isSubAttack){
						Target = SubList[Rand(mt) * SubList.size()];
						BaseAttack = 0;	//強制的にカスダメとする(暫定的な処理)
						AttackAction(Target, BaseAttack, Yours[Move].Level, Mine, MineAlived, MineCond, YoursForm, BattlePosition,
									 Yours[Move].HP, YoursCond[Move].NowHP, 1.0, YoursAttackPlus, 1.0, TURN_NIGHT);
						Logger << "　(敵軍)" << Yours[Move].Name << "が" << Mine[Target].Name << "に攻撃！\n";
						Logger << "　　残り耐久：" << MineCond[Target].NowHP << showDamage(MineCond[Target].NowHP, Mine[Target].HP) << "\n";
						if(MineAlived.size() == 0) break;
					}else{
						BaseAttack = Yours[Move].Attack + Yours[Move].Torpedo;
						int GunCount = 0, SubGunCount = 0, TorCount = 0;
						for(int j = 0; j < Yours[Move].Slots; ++j){
							BaseAttack += Yours[Move].Weapons[j].Attack;
							BaseAttack += Yours[Move].Weapons[j].Torpedo;
							if(Yours[Move].Weapons[j].Kind == "主砲"){
								++GunCount;
							}else if(Yours[Move].Weapons[j].Kind == "副砲"){
								++SubGunCount;
							}else if(Yours[Move].Weapons[j].Kind == "魚雷"){
								++TorCount;
							}
						}
						// 夜間特殊攻撃に関する処理
						//カットイン確率を計算
						int CutinPer = 0.85 * Yours[Move].Luck + 15;
						if(Move != 0) CutinPer += 15;
						if (Yours[Move].HP * 0.25 >= YoursCond[Move].NowHP){
							CutinPer += 20;
						}
						else if (Yours[Move].HP * 0.5 >= YoursCond[Move].NowHP){
							CutinPer += 10;
						}
						for(int k = 0; k < YoursShips; ++k){
							for(int j = 0; j < Yours[k].Slots; ++j){
								if((Yours[k].Weapons[j].Name == "探照灯")
								|| (Yours[k].Weapons[j].Name == "照明弾")){
									CutinPer += 5;
								}
							}
						}
						for(int k = 0; k < MineShips; ++k){
							for (int j = 0; j < Mine[k].Slots; ++j){
								if ((Mine[k].Weapons[j].Name == "探照灯")
									|| (Mine[k].Weapons[j].Name == "照明弾")){
									CutinPer -= 10;
								}
							}
						}
						if(TorCount >= 2){	//カットイン判定
							if(Rand(mt) * 100 < CutinPer){
								AttackAction(Target, BaseAttack, Yours[Move].Level, Mine, MineAlived, MineCond, YoursForm, BattlePosition,
											 Yours[Move].HP, YoursCond[Move].NowHP, 1.5, YoursAttackPlus, 1.0, TURN_NIGHT);
								AttackAction(Target, BaseAttack, Yours[Move].Level, Mine, MineAlived, MineCond, YoursForm, BattlePosition,
											 Yours[Move].HP, YoursCond[Move].NowHP, 1.5, YoursAttackPlus, 1.0, TURN_NIGHT);
								Logger << "　(敵軍)" << Yours[Move].Name << "が" << Mine[Target].Name << "にカットイン攻撃！\n";
								Logger << "　　残り耐久：" << MineCond[Target].NowHP << showDamage(MineCond[Target].NowHP, Mine[Target].HP) << "\n";
							}else{
								AttackAction(Target, BaseAttack, Yours[Move].Level, Mine, MineAlived, MineCond, YoursForm, BattlePosition,
											 Yours[Move].HP, YoursCond[Move].NowHP, 1.0, YoursAttackPlus, 1.0, TURN_NIGHT);
								Logger << "　(敵軍)" << Yours[Move].Name << "が" << Mine[Target].Name << "に攻撃！\n";
								Logger << "　　残り耐久：" << MineCond[Target].NowHP << showDamage(MineCond[Target].NowHP, Mine[Target].HP) << "\n";
							}
						}else if(GunCount >= 3){
							if(Rand(mt) * 100 < CutinPer){
								AttackAction(Target, BaseAttack, Yours[Move].Level, Mine, MineAlived, MineCond, YoursForm, BattlePosition,
											 Yours[Move].HP, YoursCond[Move].NowHP, 2.0, YoursAttackPlus, 1.0, TURN_NIGHT);
								Logger << "　(敵軍)" << Yours[Move].Name << "が" << Mine[Target].Name << "にカットイン攻撃！\n";
								Logger << "　　残り耐久：" << MineCond[Target].NowHP << showDamage(MineCond[Target].NowHP, Mine[Target].HP) << "\n";
							}else{
								AttackAction(Target, BaseAttack, Yours[Move].Level, Mine, MineAlived, MineCond, YoursForm, BattlePosition,
											 Yours[Move].HP, YoursCond[Move].NowHP, 1.0, YoursAttackPlus, 1.0, TURN_NIGHT);
								Logger << "　(敵軍)" << Yours[Move].Name << "が" << Mine[Target].Name << "に攻撃！\n";
								Logger << "　　残り耐久：" << MineCond[Target].NowHP << showDamage(MineCond[Target].NowHP, Mine[Target].HP) << "\n";
							}
						}else if((GunCount == 2) && (SubGunCount >= 1)){
							if(Rand(mt) * 100 < CutinPer){
								AttackAction(Target, BaseAttack, Yours[Move].Level, Mine, MineAlived, MineCond, YoursForm, BattlePosition,
											 Yours[Move].HP, YoursCond[Move].NowHP, 1.75, YoursAttackPlus, 1.0, TURN_NIGHT);
								Logger << "　(敵軍)" << Yours[Move].Name << "が" << Mine[Target].Name << "にカットイン攻撃！\n";
								Logger << "　　残り耐久：" << MineCond[Target].NowHP << showDamage(MineCond[Target].NowHP, Mine[Target].HP) << "\n";
							}else{
								AttackAction(Target, BaseAttack, Yours[Move].Level, Mine, MineAlived, MineCond, YoursForm, BattlePosition,
											 Yours[Move].HP, YoursCond[Move].NowHP, 1.0, YoursAttackPlus, 1.0, TURN_NIGHT);
								Logger << "　(敵軍)" << Yours[Move].Name << "が" << Mine[Target].Name << "に攻撃！\n";
								Logger << "　　残り耐久：" << MineCond[Target].NowHP << showDamage(MineCond[Target].NowHP, Mine[Target].HP) << "\n";
							}
						}else if(((GunCount == 1) || (GunCount == 2)) && (TorCount == 1)){
							if(Rand(mt) * 100 < CutinPer){
								AttackAction(Target, BaseAttack, Yours[Move].Level, Mine, MineAlived, MineCond, YoursForm, BattlePosition,
											 Yours[Move].HP, YoursCond[Move].NowHP, 1.3, YoursAttackPlus, 1.0, TURN_NIGHT);
								AttackAction(Target, BaseAttack, Yours[Move].Level, Mine, MineAlived, MineCond, YoursForm, BattlePosition,
											 Yours[Move].HP, YoursCond[Move].NowHP, 1.3, YoursAttackPlus, 1.0, TURN_NIGHT);
								Logger << "　(敵軍)" << Yours[Move].Name << "が" << Mine[Target].Name << "にカットイン攻撃！\n";
								Logger << "　　残り耐久：" << MineCond[Target].NowHP << showDamage(MineCond[Target].NowHP, Mine[Target].HP) << "\n";
							}else{
								AttackAction(Target, BaseAttack, Yours[Move].Level, Mine, MineAlived, MineCond, YoursForm, BattlePosition,
											 Yours[Move].HP, YoursCond[Move].NowHP, 1.0, YoursAttackPlus, 1.0, TURN_NIGHT);
								Logger << "　(敵軍)" << Yours[Move].Name << "が" << Mine[Target].Name << "に攻撃！\n";
								Logger << "　　残り耐久：" << MineCond[Target].NowHP << showDamage(MineCond[Target].NowHP, Mine[Target].HP) << "\n";
							}
						}else if((GunCount == 2) && (SubGunCount == 0) && (TorCount == 0)){	//連撃判定
							AttackAction(Target, BaseAttack, Yours[Move].Level, Mine, MineAlived, MineCond, YoursForm, BattlePosition,
										 Yours[Move].HP, YoursCond[Move].NowHP, 1.2, YoursAttackPlus, 1.0, TURN_NIGHT);
							AttackAction(Target, BaseAttack, Yours[Move].Level, Mine, MineAlived, MineCond, YoursForm, BattlePosition,
										 Yours[Move].HP, YoursCond[Move].NowHP, 1.2, YoursAttackPlus, 1.0, TURN_NIGHT);
							Logger << "　(敵軍)" << Yours[Move].Name << "が" << Mine[Target].Name << "に連撃！\n";
							Logger << "　　残り耐久：" << MineCond[Target].NowHP << showDamage(MineCond[Target].NowHP, Mine[Target].HP) << "\n";
						}else if((GunCount == 1) && (SubGunCount >= 1) && (TorCount == 0)){
							AttackAction(Target, BaseAttack, Yours[Move].Level, Mine, MineAlived, MineCond, YoursForm, BattlePosition,
										 Yours[Move].HP, YoursCond[Move].NowHP, 1.2, YoursAttackPlus, 1.0, TURN_NIGHT);
							AttackAction(Target, BaseAttack, Yours[Move].Level, Mine, MineAlived, MineCond, YoursForm, BattlePosition,
										 Yours[Move].HP, YoursCond[Move].NowHP, 1.2, YoursAttackPlus, 1.0, TURN_NIGHT);
							Logger << "　(敵軍)" << Yours[Move].Name << "が" << Mine[Target].Name << "に連撃！\n";
							Logger << "　　残り耐久：" << MineCond[Target].NowHP << showDamage(MineCond[Target].NowHP, Mine[Target].HP) << "\n";
						}else if((GunCount == 0) && (SubGunCount >= 2) && (TorCount <= 1)){
							AttackAction(Target, BaseAttack, Yours[Move].Level, Mine, MineAlived, MineCond, YoursForm, BattlePosition,
										 Yours[Move].HP, YoursCond[Move].NowHP, 1.2, YoursAttackPlus, 1.0, TURN_NIGHT);
							AttackAction(Target, BaseAttack, Yours[Move].Level, Mine, MineAlived, MineCond, YoursForm, BattlePosition,
										 Yours[Move].HP, YoursCond[Move].NowHP, 1.2, YoursAttackPlus, 1.0, TURN_NIGHT);
							Logger << "　(敵軍)" << Yours[Move].Name << "が" << Mine[Target].Name << "に連撃！\n";
							Logger << "　　残り耐久：" << MineCond[Target].NowHP << showDamage(MineCond[Target].NowHP, Mine[Target].HP) << "\n";
						}else{	//その他
							AttackAction(Target, BaseAttack, Yours[Move].Level, Mine, MineAlived, MineCond, YoursForm, BattlePosition,
										 Yours[Move].HP, YoursCond[Move].NowHP, 1.0, YoursAttackPlus, 1.0, TURN_NIGHT);
							Logger << "　(敵軍)" << Yours[Move].Name << "が" << Mine[Target].Name << "に攻撃！\n";
							Logger << "　　残り耐久：" << MineCond[Target].NowHP << showDamage(MineCond[Target].NowHP, Mine[Target].HP) << "\n";
						}
						if(MineAlived.size() == 0) break;
					}
				}
				if(MineAlived.size() == 0) break;
			}
			if(MineAlived.size() == 0) break;
		}
		if((YoursAlived.size() == 0) || (MineAlived.size() == 0)) break;


		for(int i = 0; i < MineShips; ++i){
			if(MineCond[i].NowHP == 0) continue;
			if(Mine[i].HP * 0.25 >= MineCond[i].NowHP) continue;
		}
		if(YoursAlived.size() == 0) break;
		for(int i = 0; i < YoursShips; ++i){
			if(YoursCond[i].NowHP == 0) continue;
			if(Yours[i].HP * 0.25 >= YoursCond[i].NowHP) continue;
		}
		if(MineAlived.size() == 0) break;
		break;
	}
	/* 8. 結果表示 */
	Logger << "【結果表示】\n";
	Logger << "　自軍：\n";
	for(int i = 0; i < MineShips; ++i){
		Logger << "　　" << Mine[i].Name << " " << MineCond[i].NowHP << "/" << Mine[i].HP << showDamage(MineCond[i].NowHP, Mine[i].HP) << "\n";
		HitPoint1[i] += MineCond[i].NowHP;
	}
	Logger << "\n　敵軍：\n";
	for(int i = 0; i < YoursShips; ++i){
		Logger << "　　" << Yours[i].Name << " " << YoursCond[i].NowHP << "/" << Yours[i].HP << showDamage(YoursCond[i].NowHP, Yours[i].HP) << "\n";
		HitPoint2[i] += YoursCond[i].NowHP;
	}
	Logger << "\n";

	return Logger.str();
}

void AttackAction(const int Target, const int BaseAttack, const int Level, const vector<kanmusu> &Yours,
                  vector<int> &YoursAlived,
                  vector<condition> &YoursCond, const FORMATION MineForm,
                  const BP BattlePosition, const int HP,
                  const int NowHP, const double NightFire,
                  const int MineAttackPlus, const double FixedShot, const TURN Turn){
	double Damage = BaseAttack;
	//命中率を算出しておく
	double EvadeSum = Yours[Target].Evade, EvadeValue;
	for(int i = 0; i < Yours[Target].Slots; ++i){
		EvadeSum += Yours[Target].Weapons[i].Evade;
	}
	if(MineForm == FOR_SUBTRAIL) EvadeSum /= 2;
	if(EvadeSum <= 37.5) EvadeValue = EvadeSum / 75; else EvadeValue = EvadeSum / (EvadeSum + 37.5);
	double HitValue = 1.0 + sqrt((Level - 1) * 5) / 100;
	HitValue -= EvadeValue;
	// キャップ前補正
	//攻撃側陣形
	bool isAttackToSub = false;
	if((Yours[Target].Kind == SC_SS) || (Yours[Target].Kind == SC_SSV)) isAttackToSub = true;
	if(((Turn == TURN_AIR) || (Turn == TURN_TOR)) && (isAttackToSub)) return;	//航空戦・雷撃戦ではノーダメ
	if(Turn == TURN_NOON){
		switch(MineForm){
			case FOR_TRAIL:
				if(isAttackToSub) Damage *= 0.45; else Damage *= 1.0;
				break;
			case FOR_SUBTRAIL:
				if(isAttackToSub) Damage *= 0.60; else Damage *= 0.8;
				break;
			case FOR_CIRCLE:
				if(isAttackToSub) Damage *= 0.90; else Damage *= 0.7;
				break;
			case FOR_ECHELON:
				if(isAttackToSub) Damage *= 0.75; else Damage *= 0.6;
				break;
			case FOR_ABREAST:
				if(isAttackToSub) Damage *= 1.0; else Damage *= 0.6;
				break;
		}
	}
	//交戦形態
	if(Turn == TURN_NOON){
		switch(BattlePosition){
			case BP_SAME:
				Damage *= 1.0;
				break;
			case BP_DIFF:
				Damage *= 0.8;
				break;
			case BP_T_Plus:
				Damage *= 1.2;
				break;
			case BP_T_Minus:
				Damage *= 0.6;
				break;
		}
	}
	//損傷
	if(Turn != TURN_AIR){
		if(HP * 0.25 >= NowHP){
			Damage *= 0.4;
		}else if(HP * 0.5 >= NowHP){
			Damage *= 0.7;
		}
	}
	//夜戦
	if(Turn == TURN_NIGHT){
		Damage *= NightFire;
	}
	// キャップを掛ける
	if(isAttackToSub){
		Damage = 100 + sqrt(Damage - 100);
	}else{
		if(Turn == TURN_NIGHT){
			Damage = 300 + sqrt(Damage - 300);
		}else{
			Damage = 150 + sqrt(Damage - 150);
		}
	}
	// キャップ後補正
	//クリティカル補正
	if(Rand(mt) < 0.15){
		Damage *= 1.5;
	}
	//触接補正
	Damage *= (100.0 + MineAttackPlus) / 100;
	//弾着修正射撃補正
	Damage *= FixedShot;
	// 最終的なダメージ量を決定
	//※弾薬量補正は無視するものとする
	Damage = Damage - Yours[Target].Defense * (Rand(mt) * 2 / 3 + 2.0 / 3);
	//夜戦での対戦攻撃では強制的にカスダメとする(暫定的な処理)
	if((Turn == TURN_NIGHT) && (isAttackToSub)) Damage = 0;
	if(Damage >= 1){
		if(Rand(mt) < HitValue){	//「回避」要素
			YoursCond[Target].NowHP -= Damage;
		}
	}else{
		if(Rand(mt) < HitValue){	//「回避」要素
			YoursCond[Target].NowHP *= (Rand(mt) * 0.08 + 0.86);
		}
	}
	if(YoursCond[Target].NowHP <= 0){
		//撃沈した際はその要素を消去する
		YoursCond[Target].NowHP = 0;
		YoursAlived.erase(remove(YoursAlived.begin(), YoursAlived.end(), Target), YoursAlived.end());
	}
}

/* main関数 */
int main(){
	// 初期設定
	//装備
	//名前・種別・火力・命中・射程
	//回避・爆装・雷装・索敵・対潜・対空・装甲
	weapon Gun_127_Multi{"12.7cm連装砲", "主砲", 2, 0, REACH_SHORT,
	                     0, 0, 0, 0, 0, 2, 0};
	weapon Gun_100_Multi_Ko{"10cm連装高角砲", "主砲", 2, 0, REACH_SHORT,
	                     0, 0, 0, 0, 0, 7, 0};
	weapon Gun_203_Multi{"20.3cm連装砲", "主砲", 8, 0, REACH_MEDIUM,
		0, 0, 0, 0, 0, 3, 0};
	weapon Gun_356_Multi{"35.6cm連装砲", "主砲", 15, 0, REACH_LONG,
		0, 0, 0, 0, 0, 4, 0};
	weapon Torpedo_61_3{"61cm三連装魚雷", "魚雷", 0, 0, REACH_SHORT,
	                     0, 0, 5, 0, 0, 0, 0};
	weapon Torpedo_61_4_Oxy{"61cm四連装(酸素)魚雷", "魚雷", 0, 0, REACH_SHORT,
		0, 0, 5, 0, 0, 0, 0};
	weapon WB_Zuiun{"瑞雲", "水爆", 0, 1, REACH_NONE,
	                0, 4, 0, 6, 4, 2, 0};
	weapon WS_Zeroshiki{"零式水上偵察機", "水偵", 0, 1, REACH_NONE,
	                    0, 1, 0, 5, 2, 1, 0};
	weapon PF_Zero_21{"零式艦戦21型", "艦戦", 0, 0, REACH_NONE,
		0, 0, 0, 0, 0, 5, 0};
	weapon PB_99{"九九式艦爆", "艦爆", 0, 0, REACH_NONE,
		0, 5, 0, 0, 3, 0, 0};
	weapon PA_97{"九七式艦攻", "艦攻", 0, 0, REACH_NONE,
		0, 0, 5, 1, 4, 0, 0};
	weapon None{"未装備", "無し", 0, 0, REACH_SHORT, 0, 0, 0, 0, 0, 0, 0};
	//回避・爆装・雷装・索敵・対潜・対空・装甲
	//艦娘
	//名前・艦種・スロット数・耐久・火力・雷装・対空・装甲・回避・対潜・索敵・射程・運・速力
	kanmusu Fubuki_Fubuki("吹雪", SC_DD, 1, 2, 15, 10, 27, 10, 5, 40, 20, 5, REACH_SHORT, 17, SPEED_HIGH);
		Fubuki_Fubuki.Weapons[0] = Gun_127_Multi;
		Fubuki_Fubuki.Weapons[1] = Torpedo_61_3;
		Fubuki_Fubuki.Airs[0] = 0;
		Fubuki_Fubuki.Airs[1] = 0;
	kanmusu Kuma_Oi("大井改", SC_CLT, 10, 2, 32, 8, 80, 13, 14, 37, 28, 11, REACH_MEDIUM, 10, SPEED_HIGH);
		Kuma_Oi.Weapons[0] = Torpedo_61_4_Oxy;
		Kuma_Oi.Weapons[1] = Torpedo_61_4_Oxy;
		Kuma_Oi.Airs[0] = 0;
		Kuma_Oi.Airs[1] = 0;
	kanmusu Mogami_Mogami("最上改", SC_CAV, 10, 4, 50, 28, 23, 24, 39, 38, 0, 25, REACH_MEDIUM, 10, SPEED_HIGH);
		Mogami_Mogami.Weapons[0] = Gun_203_Multi;
		Mogami_Mogami.Weapons[1] = WB_Zuiun;
		Mogami_Mogami.Weapons[2] = WS_Zeroshiki;
		Mogami_Mogami.Weapons[3] = None;
		Mogami_Mogami.Airs[0] = 5;
		Mogami_Mogami.Airs[1] = 6;
		Mogami_Mogami.Airs[2] = 5;
		Mogami_Mogami.Airs[3] = 3;
	kanmusu Akagi_Akagi("赤城", SC_CV, 1, 4, 69, 0, 0, 32, 28, 28, 0, 44, REACH_SHORT, 12, SPEED_HIGH);
		Akagi_Akagi.Weapons[0] = PF_Zero_21;
		Akagi_Akagi.Weapons[1] = PB_99;
		Akagi_Akagi.Weapons[2] = PA_97;
		Akagi_Akagi.Weapons[3] = None;
		Akagi_Akagi.Airs[0] = 18;
		Akagi_Akagi.Airs[1] = 18;
		Akagi_Akagi.Airs[2] = 27;
		Akagi_Akagi.Airs[3] = 10;
	kanmusu Ise_Ise("伊勢改", SC_BBV, 10, 4, 77, 63, 0, 45, 75, 36, 0, 22, REACH_LONG, 30, SPEED_LOW);
		Ise_Ise.Weapons[0] = Gun_356_Multi;
		Ise_Ise.Weapons[1] = WB_Zuiun;
		Ise_Ise.Weapons[2] = None;
		Ise_Ise.Weapons[3] = None;
		Ise_Ise.Airs[0] = 11;
		Ise_Ise.Airs[1] = 11;
		Ise_Ise.Airs[2] = 11;
		Ise_Ise.Airs[3] = 14;
	kanmusu E_E401("伊401(い401)", SC_SSV, 1, 1, 20, 2, 36, 0, 5, 13, 0, 15, REACH_SHORT, 20, SPEED_LOW);
		E_E401.Weapons[0] = None;
		E_E401.Airs[0] = 3;
	kanmusu Fubuki_Fubuki2("吹雪改", SC_DD, 99, 3, 30, 49, 79, 49, 49, 89, 59, 39, REACH_SHORT, 12, SPEED_HIGH);
		Fubuki_Fubuki2.Weapons[0] = Gun_100_Multi_Ko;
		Fubuki_Fubuki2.Weapons[1] = Gun_100_Multi_Ko;
		Fubuki_Fubuki2.Weapons[2] = None;
		Fubuki_Fubuki2.Airs[0] = 0;
		Fubuki_Fubuki2.Airs[1] = 0;
		Fubuki_Fubuki2.Airs[2] = 0;
	//名前・艦種・スロット数・耐久・火力・雷装・対空・装甲・回避・対潜・索敵・射程・運・速力

	// 対戦シミュレーション
	//艦隊を定義
	vector<kanmusu> First_Kantai{Fubuki_Fubuki, Kuma_Oi, Mogami_Mogami, Akagi_Akagi, Ise_Ise, E_E401};
	vector<kanmusu> Second_Kantai{E_E401, Ise_Ise, Akagi_Akagi, Mogami_Mogami, Kuma_Oi, Fubuki_Fubuki};
	//vector<kanmusu> First_Kantai{Fubuki_Fubuki, Fubuki_Fubuki, Fubuki_Fubuki, Fubuki_Fubuki, Fubuki_Fubuki, Fubuki_Fubuki};
	//vector<kanmusu> Second_Kantai{Fubuki_Fubuki2, Fubuki_Fubuki2, Fubuki_Fubuki2, Fubuki_Fubuki2, Fubuki_Fubuki2, Fubuki_Fubuki2};

	//対戦
	const int count = 10000;
	while(1){
		vector<double> HitPoint1(First_Kantai.size(), 0.0), HitPoint2(Second_Kantai.size(), 0.0);
		string log;
		for(int i = 0; i < count; ++i){
			log = simulate(First_Kantai, Second_Kantai, FOR_TRAIL, FOR_TRAIL, HitPoint1, HitPoint2);
		}
		//cout << log << "\n";
		cout << "[1]\n";
		for(int i = 0; i < First_Kantai.size(); ++i){
			HitPoint1[i] /= count;
			cout << First_Kantai[i].Name << " " << HitPoint1[i] << "/" << First_Kantai[i].HP << showDamage(HitPoint1[i], First_Kantai[i].HP) << "\n";
		}
		cout << "[2]\n";
		for(int i = 0; i < Second_Kantai.size(); ++i){
			HitPoint2[i] /= count;
			cout << Second_Kantai[i].Name << " " << HitPoint2[i] << "/" << Second_Kantai[i].HP << showDamage(HitPoint2[i], Second_Kantai[i].HP) << "\n";
		}
		break;
	}
	cout << "\n";
	while(1){
		vector<double> HitPoint1(Second_Kantai.size(), 0.0), HitPoint2(First_Kantai.size(), 0.0);
		string log;
		for(int i = 0; i < count; ++i){
			log = simulate(Second_Kantai, First_Kantai, FOR_TRAIL, FOR_TRAIL, HitPoint1, HitPoint2);
		}
		//cout << log << "\n";
		cout << "[1]\n";
		for(int i = 0; i < Second_Kantai.size(); ++i){
			HitPoint1[i] /= count;
			cout << Second_Kantai[i].Name << " " << HitPoint1[i] << "/" << Second_Kantai[i].HP << showDamage(HitPoint1[i], Second_Kantai[i].HP) << "\n";
		}
		cout << "[2]\n";
		for(int i = 0; i < First_Kantai.size(); ++i){
			HitPoint2[i] /= count;
			cout << First_Kantai[i].Name << " " << HitPoint2[i] << "/" << First_Kantai[i].HP << showDamage(HitPoint2[i], First_Kantai[i].HP) << "\n";
		}
		break;
	}
}

/* 【サンプルデータ】
   吹雪・大井改・最上改・赤城・伊勢改・伊401を使用(最低Lv・初期装備とする)
   第1艦隊：吹雪・大井改・最上改・赤城・伊勢改・伊401
   第2艦隊：伊401・伊勢改・赤城・最上改・大井改・吹雪
   第1艦隊が第2艦隊に攻撃する場合と、その反対の場合とで計算した。
*/
/* 【実行例】
[1]
吹雪Lv1 12.3246/15(健在)
大井改Lv10 26.6857/32(健在)
最上改Lv10 42.1975/50(健在)
赤城Lv1 55.7807/69(健在)
伊勢改Lv10 64.7224/77(健在)
伊401(い401)Lv1 4.7671/20(大破)
[2]
伊401(い401)Lv1 8.1371/20(中破)
伊勢改Lv10 63.2695/77(健在)
赤城Lv1 53.6346/69(健在)
最上改Lv10 40.1464/50(健在)
大井改Lv10 25.211/32(健在)
吹雪Lv1 10.8624/15(小破)

[1]
伊401(い401)Lv1 5.9317/20(大破)
伊勢改Lv10 64.3501/77(健在)
赤城Lv1 55.4527/69(健在)
最上改Lv10 41.9878/50(健在)
大井改Lv10 26.5382/32(健在)
吹雪Lv1 12.2416/15(健在)
[2]
吹雪Lv1 12.2614/15(健在)
大井改Lv10 26.368/32(健在)
最上改Lv10 41.5914/50(健在)
赤城Lv1 54.5511/69(健在)
伊勢改Lv10 63.3445/77(健在)
伊401(い401)Lv1 4.3472/20(大破)
*/

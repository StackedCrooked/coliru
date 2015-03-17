#include <iostream>
#include <string>
#include <vector>

using namespace std;

using Texture = int; //Pas de SFML sous la main
//   /!\ sprite_ sera toujours un sf::Sprite /!\

//############Methode 1#################
class BulletModel
{
    public:
    BulletModel(Texture const& tex) : tex_(tex) {}
    Texture const& getTexture() const {return tex_;}
    private:
    Texture tex_;
};
/* du coup tu te retrouve avec un conteneur de modèle de balles :
(Ici c'est un vector mais tu peux utiliser un objet, je fais au plus simple*/
vector<BulletModel> BulletModelHolder;
//là tu initialise tes modèles
//Et ensuite ta classe Bullet ressemble à ça :
class Bullet
{
    public:
    Bullet(/*...*/BulletModel const& model) : model_(model)/*, sprite_(model.getTexture)*/ {}
    private:
    BulletModel const& model_;
};
/*On utilisera ça comme ça pour déclarer un Bullet
Bullet(DES_PARAMETRES, BulletModelHolder[1]);
*/

//###############Methode 2##############
//Note qu'ici si tu stockes juste une texture autant faire un conteneur de Texture directement au lieu de passer par une class de plus !
vector<Texture> TextureHolder; //à remplir
class BBullet
{
    public:
    BBullet(/*...*/Texture const& tex) /*: sprite_(tex)*/ {}
    //Note : pas besoin de stocker la texture ici, on stocke directement un sf::Sprite
};
/*On appellera donc ça de cette manière : 
BBullet(DES_PARAMETRES, TextureHolder[1]);
*/

//################Methode 3##############
//Le modèle de balle, fixé en dur dans le code.
class DefaultBulletModel
{
    public:
    static Texture const& getTexture()
    {
        if (!initialized_) //on aura une seule instance de tex_ et on ne l'initialisera qu'une seule fois
        {
            tex_ = 42;//On initialise la texture
            initialized_ = true;
        }
        return tex_;
    }
    private:
    static Texture tex_;
    static bool initialized_;
};
bool DefaultBulletModel::initialized_ = false; //Obligatoire

template <typename BulletModel>
class CBullet //Note : si le paramètre template n'a pas de fonction static getTexture() ça ne compilera pas.
{
    public:
    CBullet(/*...*/) /*: sprite_(BulletModel::getTexture())*/ {}
    private:
    //sf::Sprite sprite_;
};
/*On créera donc une balle comme ça :
CBullet<BalleOrange>(DES_PARAMETRES);
*/
/*Note de fin :
J'ai fait les codes vite fait, si il y a un problème signale-le moi ;)
*/

int main()
{
    
}

#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;
int main ()

{
    double a,b,c,d,r,q,p,m,g,v,t,u,j,y,z,e,h,i,k,l,o,aa,ab,bb;
	double waga, zawtl;
	int ii,nn,km,wiek,wzrost,masa,aktywnosc,powtorzenia;                                   // plec: 1=kobieta, 2=mezczyzna
	string imie, sylw,aaa;
	double zapot1,zapot2,pozostalo,kk,masaproduktu;
	string Tt[101];
    double Tk[101];
    Tt[0]="ananas";
    Tk[0]=54;
    Tt[1]="arbuz";
    Tk[1]=36;
    Tt[2]="banan";
    Tk[2]=96;
    Tt[3]="barszcz";
    Tk[3]=55;
    Tt[4]="baton";
    Tk[4]=451;
    Tt[5]="bigos";
    Tk[5]=119;
    Tt[6]="brokula";
    Tk[6]=28;
    Tt[7]="brzoskwinia";
    Tk[7]=46;
    Tt[8]="bulka";
    Tk[8]=296;
    Tt[9]="buraki";
    Tk[9]=70;
    Tt[10]="chipsy";
    Tk[10]=530;
    Tt[11]="chleb";
    Tk[11]=280;
    Tt[12]="coca_cola";
    Tk[12]=42;
    Tt[13]="nalesniki";
    Tk[13]=174;
    Tt[14]="czekolada";
    Tk[14]=520;
    Tt[15]="herbatniki";
    Tk[15]=431;
    Tt[16]="kotlet_z_piersi_kurczaka";
    Tk[16]=142;
    Tt[17]="jablko";
    Tk[17]=46;
    Tt[18]="jajko";
    Tk[18]=115;
    Tt[19]="jogurt";
    Tk[19]=70;
    Tt[20]="kabanosy";
    Tk[20]=326;
    Tt[21]="karp";
    Tk[21]=100;
    Tt[22]="kasza_manna";
    Tk[22]=348;
    Tt[23]="kielbasa";
    Tk[23]=230;
    Tt[24]="lody";
    Tk[24]=114;
	Tt[25]="mleko";
    Tk[25]=50;
    Tt[26]="orzechy";
    Tk[26]=630;
    Tt[27]="paluszki";
    Tk[27]=348;
    Tt[28]="paprykarz";
    Tk[28]=181;
    Tt[29]="parowki";
    Tk[29]=260;
    Tt[30]="pepsi";
    Tk[30]=42;
    Tt[31]="paczki";
    Tk[31]=376;
    Tt[32]="pierogi";
    Tk[32]=216;
    Tt[33]="pizza_margarita";
    Tk[33]=320;
    Tt[34]="popcorn";
    Tk[34]=397;
    Tt[35]="platki_sniadaniowe";
    Tk[35]=370;
    Tt[36]="pomidor";
    Tk[36]=30;
    Tt[37]="prince_polo";
    Tk[37]=534;
    Tt[38]="ryz";
    Tk[38]=350;
    Tt[39]="truskawki";
    Tk[39]=35;
    Tt[40]="zupa_pomidorowa";
    Tk[40]=35;
    Tt[41]="zupa_ogorkowa";
    Tk[41]=42;
    Tt[42]="zorek";
   	Tk[42]=124; 
   	Tt[43]="maslo";
    Tk[43]=748;
    Tt[44]="kakao";
    Tk[44]=448;
    Tt[45]="miod";
    Tk[45]=324;
    Tt[46]="makrela";
    Tk[46]=221;
    Tt[47]="ser_feta";
    Tk[47]=215;
    Tt[48]="kisiel";
    Tk[48]=121;
    Tt[49]="flaki";
    Tk[49]=81;
    Tt[50]="cheeseburger";
    Tk[50]=277;
    Tt[51]="frytki";
    Tk[51]=260;
    Tt[52]="hamburger";
    Tk[52]=267;
    Tt[53]="cukier";
    Tk[53]=402;
    Tt[54]="nimm_2";
    Tk[54]=368;
    Tt[55]="bor_seto";
    Tk[55]=312;
    Tt[56]="pierniczki";
    Tk[56]=340;
    Tt[57]="precelki";
    Tk[57]=390;
    Tt[58]="sernik";
    Tk[58]=233;
    Tt[59]="tymbark";
    Tk[59]=39;
    Tt[60]="sprite";
    Tk[60]=42;
    Tt[61]="sok";
    Tk[61]=55;
    Tt[62]="bagietka";
    Tk[62]=285;
    Tt[63]="kaczka";
    Tk[63]=343;
    Tt[64]="kurczak";
    Tk[64]=250;
    Tt[65]="sledz";
    Tk[65]=270;
    Tt[66]="pieczarki";
    Tk[66]=331;
    Tt[67]="dorsz";
    Tk[67]=78;
    Tt[68]="dynia";
    Tk[68]=28;
    Tt[69]="pestki_z_dynii";
    Tk[69]=566;
    Tt[70]="gruszka";
    Tk[70]=54;
    Tt[71]="agrest";
    Tk[71]=41;
    Tt[72]="twixa";
    Tk[72]=451;
    Tt[73]="czeresnie";
    Tk[73]=61;
    Tt[74]="pasztet";
    Tk[74]=390;
    Tt[75]="szynka_z_kurczaka";
    Tk[75]=89;
    Tt[76]="salatka_z_makreli";
    Tk[76]=181;
    Tt[77]="maliny";
    Tk[77]=29;
    Tt[78]="nektaryna";
    Tk[78]=48;
    Tt[79]="ogorek_kwaszony";
    Tk[79]=13;
    Tt[80]="ogorek";
    Tk[80]=11;
    Tt[81]="pierogi_ruskie";
    Tk[81]=166;
    Tt[82]="pierogi_z_miesem";
    Tk[82]=219;
    Tt[83]="pierogi_z_serem";
    Tk[83]=238;
    Tt[84]="marchew";
    Tk[84]=27;
    Tt[85]="porzeczki_czarne";
    Tk[85]=35;
    Tt[86]="ryz_preparowany";
    Tk[86]=361;
    Tt[87]="rzodkiewka";
    Tk[87]=14;
    Tt[88]="salami";
    Tk[88]=548;
    Tt[89]="salatka_warzywna";
    Tk[89]=80;
    Tt[90]="sardynki_w_oleju";
    Tk[90]=221;
    Tt[91]="ser_feta";
    Tk[91]=215;
    Tt[92]="sok_ananasowy";
    Tk[92]=48;
    Tt[93]="salatka_owocowa";
    Tk[93]=102;
    Tt[94]="winogrona";
    Tk[94]=69;
    Tt[95]="milk_shake";
    Tk[95]=380;
    Tt[96]="energy_drink";
    Tk[96]=60;
    Tt[97]="cappucino";
    Tk[97]=415;
    Tt[98]="herbata_lipton";
    Tk[98]=4;
    Tt[99]="sok_jablkowy";
    Tk[99]=48;
    Tt[100]="kotlet_schabowy";
    Tk[100]=351;
	

	cout << "\n\n  Program multikalkulator obliczajacy np. BMI, WHR \n";
	cout<<"  oraz ilosc kalorii potrzebnych do prawidlowej diety. Kamil Palka \n";
	cout <<"  I LO im. Powstancow Slaskich w Rybniku \n\n\n";
		cout<<endl<<endl;
		cout<<"witaj w programie! wybierz tryb: "<<endl;
		cout<<endl;
		cout<<" 1 - program oblicza twoje wskazniki dietetyczne"<<endl;
		cout<<endl;
		cout<<" 2 - program oblicza ile jeszcze kalori mozesz zjesc by miec idealna diete"<<endl;
		cout<<endl;
		cout<<"potwierdz (1 lub 2): ";
			cin>>bb;
			
			cout<<endl<<endl;
			if(bb==1){
			
		
	cout << "podaj swoje imie : \t\t";
   cin >> imie;
   if((imie[imie.size()-1] == 'a') && (imie != "Kuba")) km=1;
       else km=2;
   if( km==1 )			// określeni płci, wypisywanie imienia
	    cout << "    Plec: kobieta \n\t Podaj mase ciala [zaokr. do kg]: \t";
   else
	    cout << "    Plec: mezczyzna \n\t Podaj mase ciala [zaokr. do kg]:\t";
	cin>>a;
	while(a<=0) { 
       cout<<"\t\t masa ciala musi byc dodatnia"<<endl;
       cout<<"\t\t Podaj mase ciala [zaokr. do kg ]:  \t"; 
       cin>>a;
       }	

	cout<<"\t Podaj wzrost [zaokr. do cm]: \t\t\t";
	cin>>b;
	while(b<=0) { 
      cout<<"\t\t wzrost musi byc dodatni \n";
      cout<<"\t\t Podaj wzrost [cm]:  \t\t"; 
      cin>>b;
      }
	
	r = (a/((b*b)/10000));
   cout<<"\t Twoje BMI wynosi: \t\t\t"<<r<< " i ozn. ";
	if ( r > 25 )
		cout<<"otylosc \n";
	else if ( r > 23 )
		cout<<"granice otylosci \n";
	   else if ( r > 18.5)
		     cout<<"norme \n";
	        else
		         cout<<"niedowage \n";		         
	cout << "\t wg wzoru Lorentza twoja prawidlowa waga to \t";  // waga Lorentza
	  p= b - 100 - (b - 150)/2;
	  q= b - 100 - (b - 150)/4;

   if(km==1) waga = p; else waga = q;  		 //kobieta lub mezczyzna
	cout <<waga <<" kg \n";         
	   
   cout << "\n\n Sprawdzimy teraz, jakiej jestes budowy ciala:  "<<endl;		// budowa ciala
   cout << "\t podaj obwod nadgarstka [zaokr. do cm]: \t";
   cin>>m;
	while(m<=0) { 
     cout<<"\t\t obwod nadgarstka musi byc dodatni  \n";
     cout<<"\t podaj obwod nadgarstka [cm]:  \t\t"; 
     cin>>m;
     }
	if ( m > 17.5 )
	   sylw = "masywna (grubokoscisty)";
	else if ( m < 15.5 )
		sylw = "drobna (drobnokoscisty)";
	else
	sylw = "srednia (sredniokoscisty)";
		cout<<"\t budowa " <<sylw<<" \n";

  cout <<"\n Procentowa zawartosc tkanki tluszczowej w organizmie (wg metody YMCA) (+-3%)  \n"; // metoda YMCA
  cout<<"\t podaj obwod talii [cm]: \t";
  cin>>g;
  while(g<=0) { 
      cout<<"\t\t obowod talii musi byc dodatni \n";
      cout<<"\t podaj obwod talii [cm] :  \t"; 
      cin>>g;
      }
   
  v = (1.634*g - 0.1804*a - 76.76)/(2.2*a)*100;
  o = (1.634*g - 0.1804*a - 98.42)/(2.2*a)*100;
  if(km==1) zawtl = v; else zawtl = o;      	  //kobieta lub mezczyzna
  cout<<" \t twoja % zawartosc tluszczu wynosi: \t"<<zawtl<<endl;        

  cout << "\n\n Czym by byla dieta bez obliczenia podstawowej przemiany materii (PPM)?  \n";
  cout << "    obliczymy ja z wzoru Harrisa i Benedicta:  \n";
  cout << "\t podaj ile masz lat:  \t";
  cin>>u;
  while(u<=0) { 
      cout<<"\t\t liczba lat musi byc dodatnia\n";
      cout<<"\t podaj ile masz lat: \t"; 
      cin>>u;
      }
  y=665.1 + 9.567*a + 1.85*b - 4.68*u;
  j=66.47 + 13.7*a +  5.0*b - 6.76*u;
  if(km==1) cout<<"  \t aby zapewnić PPM, potrzebujesz : " <<y<< " kcal \n"; 		 //kobieta
  else cout<<"  \t aby zapewnic PPM, potrzebujesz : "<<j<< " kcal \n";           // menzczyzna
	
  cout << "\n\n Gdy wiesz juz, ile kcal potrzebujesz na PPM, dowiedz sie, ile potrzebujesz CPM  \n";
  cout << " \t Okresl swoja aktywnosc fizyczna i odczytaj wynik:  \n";
  z=y*1.4;
  e=y*1.5;
  h=y*1.6;
  i=j*1.4;
  k=j*1.5;
  l=j*1.6;
  if(z==1) cout<<"\n\t\t mala (siedzacy tryb życia): \t\t\t" <<z<<"\n\t\t srednia (np. cwiczenia 2 razy w tygodniu): \t" <<e<< "\n\t\t duza (np. ćwiczenia 3-4 razy w tygodniu): \t" <<h<<endl;
  	else   cout<<"\n\t\t mala (siedzacy tryb zycia): \t\t\t" <<i<< "\n\t\t srednia (np. cwiczenia 2 razy w tygodniu): \t" <<k<< "\n\t\t duza (np. ćwiczenia 3-4 razy w tygodniu): \t" <<l<<endl;
  
  
  cout << "\n\n Jako ostatni wskaznik obliczymy twoje WHR:  \n";
  cout<<"\t podaj obwod bioder [cm]: \t";
  cin>>aa;
  while(aa<=0) { 
      cout<<"\t\t obwod bioder musi byc liczba dodatnia  \n";
      cout<<"\t\t podaj obwod bioder [cm]: \t"; 
      cin>>aa;
      }
  ab=g/aa;
  cout<<"\t twoje WHR wynosi: \t" <<ab;

  if(km==1) if (ab<=0,8) cout<<"\t sylwetka typu gruszka  \n";
	         else cout<<" - sylwetka typu jablko  \n";		  
       else if (ab<=1) cout <<" - sylwetka typu gruszka  \n";
            else cout <<" - sylwetka typu jablko  \n";
	 
	 cout<<"\n\n\n podsumujmy TWOJE wyniki:  \n\n";	 
	 cout<<"\t                 twoje BMI wynosi: \t"<<r<<endl;
	 cout<<"\t        twoja idealna masa wynosi: \t"<<waga<<endl;
	 cout<<"\t            twoja budowa ciala to: \t"<<sylw<<endl;
	 cout<<"\ttwoja % zawartosc tluszczu wynosi: \t"<<zawtl<<endl;
	 cout<<"\t      ilosc kcal, by zapewnic PPM: \t" ;
	 if(km==1) cout <<""<<y<<endl ; 		 //kobieta
     else cout<<""<<j<<endl ;           // menzczyzna<<endl; 
	 cout<<"\t      ilosc kcal, by zapewnic CPM: \t";
	 if(z==1) cout<<"\n\t\t mala (siedzacy tryb życia): \t\t\t" <<z<<"\n\t\t srednia (np. cwiczenia 2 razy w tygodniu): \t" <<e<< "\n\t\t duza (np. ćwiczenia 3-4 razy w tygodniu): \t" <<h<<endl;
  	 else   cout<<"\n\t\t mala (siedzacy tryb zycia): \t\t\t" <<i<< "\n\t\t srednia (np. cwiczenia 2 razy w tygodniu): \t" <<k<< "\n\t\t duza (np. ćwiczenia 3-4 razy w tygodniu): \t" <<l<<endl;
	 cout<<"\t                        twoje WHR: \t"<<ab<<endl;
	 cout<<"\t                twoj typ sylwetki: \t";
	 if(km==1) if (ab<=0,8) cout<<"\t - sylwetka typu gruszka  \n";
	         else cout<<" - sylwetka typu jablko  \n";		  
       else if (ab<=1) cout <<" - sylwetka typu gruszka  \n";
            else cout <<" - sylwetka typu jablko  \n";
cout <<"\n\n\n";
system ("pause");
return 0;
}
else  cout<<"oblicz twoje dzienne zapotrzebowanie kaloryczne"<<endl<<endl<<endl;
 
cout << "podaj swoje imie : \t\t";
   cin >> imie;
   if((imie[imie.size()-1] == 'a') && (imie != "Kuba")) km=1;
       else km=2;
   if( km==1 )
   cout << "    Plec: kobieta \n\t Podaj swoj wiek: \t";
   else
   cout << "    Plec: mezczyzna \n\t Podaj swoj wiek:\t";
   cin>>wiek;
   cout<<endl;
   cout<<"podaj swoj wzrost: \t\t";
   cin>>wzrost;
   cout<<endl;
   cout<<"podaj swoja mase ciala: \t";
   cin>>masa;
   cout<<endl;
   cout<<"wybierz swoja aktywnosc fizyczna: \t";
   cout<<endl;
   cout<<"\t\t1-mala (siedzacy tryb zycia)"<<endl;
   cout<<endl;
   cout<<"\t\t2-srednia (np. cwiczenia 2 razy w tygodniu"<<endl;
   cout<<endl;
cout<<"\t\t3-duza (np. cwiczenia 3-4 razy w tygodniu"<<endl;
   cout<<endl;
cout<<"potwierdz swoja aktywnosc (1-3): \t";
cin>>aktywnosc;
        cout<<endl<<endl;
 
 if(km==1)zapot1=(665.1 + 9.567*masa + 1.85*wzrost - 4.68*wiek);
 else zapot2=(66.47 + 13.7*masa +  5.0*wzrost - 6.76*wiek);
 
   if(km==1)
   {
 
   if(aktywnosc==1)zapot1=(zapot1*14)/10;
   if(aktywnosc==2)zapot1=(zapot1*15)/10;
   if(aktywnosc==3)zapot1=(zapot1*16)/10;
}
 
else
 
   if(aktywnosc==1)zapot2=(zapot2*14)/10;
   if(aktywnosc==2)zapot2=(zapot2*15)/10;
   if(aktywnosc==3)zapot2=(zapot2*16)/10;
 
 
 
   if(km==1) cout<<"twoje zapotrzebowanie energetyczne wynosi: "<<zapot1<<endl;
   else cout<<"twoje zapotrzebowanie energetyczne wynosi: "<<zapot2<<endl;
 
   if (km==1)pozostalo=zapot1;
   else pozostalo=zapot2;
 
 if(km==1)
 	{
 
 cout<<"ile dzis juz zjadlas/wypilas produktow spozyczych : ";
 cin>>nn;
	}
 else 
	 {
 	cout<<"ile dzis juz zjadles/wypiles produktow spozyczych : ";
    cin>>nn;
	}
 
while(nn>0)
{

    if (km==1)
	{
    
	cout<<"\n co dzis zjadlas/wypilas: ";
    cin>>aaa;
	kk=0;
	}
   else 
   {
   
	cout<<"\n co dzis zjadles/wypiles: "; 
    cin>>aaa;
    kk=0;
	}
    
	for(ii=0;ii<101;ii++)
      if (Tt[ii]==aaa)
      {
                   if (km==1)
				   {
                   
				   cout<<"ile gram produktu zjadlas/wypilas: ";
                   cin>>masaproduktu;
                   masaproduktu=masaproduktu/100;
   					
					}
				else {
				
				   cout<<"ile gram produktu zjadles/wypiles: ";
                   cin>>masaproduktu;
                   masaproduktu=masaproduktu/100;
					}
				   
				if(km==1)  
				{
				cout<<"\n zjadlas/wypilas "<<Tk[ii]*masaproduktu<<" kcal";
				kk = Tk[ii]*masaproduktu;
				}
      			else
				  {
      			
				  cout<<"\n zjadlaes/wypiles "<<Tk[ii]*masaproduktu<<" kcal";
      				kk = Tk[ii]*masaproduktu;
				}
      }
    if (kk==0)
         {
         cout<<"\n produktu nie ma w bazie danych wpisz ile ten produkt ma kalori: ";
         cin>>kk;
         
		 if(km==1){ cout<<"ile gram produktu zjadlas/wypilas: ";
                   cin>>masaproduktu;
                   masaproduktu=masaproduktu/100;
                   kk=kk*masaproduktu;
                   cout<<"\n zjadlas/wypilas "<<kk<<" kcal";
				  }
		 
		 else{
		 
		 cout<<"ile gram produktu zjadles/wypiles: ";
                   cin>>masaproduktu;
                   masaproduktu=masaproduktu/100;
                   kk=kk*masaproduktu;
                   cout<<"\n zjadlaes/wypiles "<<kk<<" kcal";
				}
         }
    pozostalo = pozostalo - kk;
    cout<<"\n mozesz jeszcze zjesc/wypic  " <<pozostalo;
    nn--;
}
cout<<endl<<endl;
                 if(pozostalo>0)cout<<"aby zapewnic optymalna diety zjedz/wypij jeszcze: "<<pozostalo<<" kcal"<<endl<<endl;
                 else if(km==1){
						cout<<"zjadlas/wypilas o: "<<pozostalo<<" kcal za duzo aby zapewnic optymalna diete "<<endl<<endl<<endl<<endl;
					}
                 
				 else {
				 cout<<"zjadles/wypiles o: "<<pozostalo<<" kcal za duzo aby zapewnic optymalna diete "<<endl<<endl<<endl<<endl;
				}

system ("pause");
return 0;
}


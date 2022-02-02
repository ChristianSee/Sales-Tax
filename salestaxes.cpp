//*****************************************************
//**                                                 **
//** By: Christian Seepold                           **
//** Thema: Receipt with salestaxes                  **
//** Datum: 02.02.2022                               **
//** Status: ready                                   **
//**                                                 **
//*****************************************************

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <limits>

using namespace std;

//Zum Lesen und Schreiben in Datei
ofstream of_schreiben;
ifstream if_lesen;
const string s_data = "art.txt";

//Funktionsprototypen
double anzeige(void);
double runde();
double rech1();
double rech2();
int eingaber();
int eingabef();


//Funktion zum Schreiben in Datei
double anzeige(int &a, double &b, double &c, char *d)
{
    of_schreiben.open(s_data.c_str(), ios::app);    //öffnen der Datei und anhängen der Daten
    of_schreiben << a << " \t\t";                   //Anzahl   
    of_schreiben << " " << d << " \t\t";            //Name
    of_schreiben << " " << c << " \t ";             //Preis
    of_schreiben << " " << b << " \t \n";           //Steuer
    of_schreiben.close();                           //Datei schliessen
    return 0;
}

//Funktion zum Runden der Steuer
double runde(double& zahl) {
    zahl = ceil(zahl * 20); // 0.05 entspricht 1/20
    zahl = zahl / 20;
    return zahl;
}

//Berechnungen der Preise incl. Steuer
double rech1(int &r1, int &r2, double &pr) {
    double tax1 = pr + r1;
    double summe = r2 * tax1;
    return summe;
}

double rech2(int &s1, double &s2, double &spr) {
    runde(s2);
    double summe = s1 * spr + s2;
    return summe;
}

//Funktionen zum Ueberprüfen ob Zahl eingegeben wurde
int eingaber(int &a, char *d) {
    if (cin.fail() == false) {      //Eingabe war korrekt
        cout << d << "buyed \n";
    }
    else                            // Eingabe war nicht korrekt
    {
        return a;
    }
}
int eingabef(int &a) {
    cin >> a;
    while (!(cin >> a)) {
        cin.clear();                //Falsche Eingaben haben keine Auswirkung auf nächste Eingabe
        cout << "How many? ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Eingabestream wird geloescht und neue Zeile wird eingelesen
    }
    return 0;
}

//Main-Funktion
int main()
{
    //Variablen
    int anzahl, basetax;
    char article[20];
    
    //Artikelpreise
    double b1 = 12.49, m1 = 14.99, c1 = 0.85, ic1 = 10.00, ip1 = 27.99, ipe1 = 47.50, p1 = 18.99, h1 = 9.75, ice1 = 11.25;

    //Initialisierung für Steuer und Gesamtsumme
    double tax_b = 0, tax_m = 0 , tax_c = 0 , tax_ic = 0, tax_ice = 0, tax_ip = 0, tax_ipe = 0, tax_p = 0, tax_h = 0;
    double summe_b = 0, summe_m = 0, summe_c = 0, summe_ic = 0, summe_ice = 0, summe_ip = 0, summe_ipe = 0, summe_p = 0, summe_h = 0;
    
      
    //Begruessung
    cout << "Welcome to our store, what do you like to purchase? \n \n";

    do {
        //Auswahlmenue
        cout << "Please Enter \n b for book \n m for music \n c for chocolate bar \n ic for importet box of chocolate (price at 10.00) \n" 
             << " ice for importet box of chocolate (price at 11.25) \n ip for importet bottle of perfume (price at 27.99) \n ipe for importet bottle of perfume (price at 47.50)"
             << "\n p for bottle of perfume \n h for packet of headache pills \n\n end for the end of your purchase \n\n confirm every choice with enter \n\n ";
        cin >> article;

        //Unterscheidung der Steuersaetze
        if (article == string("b") || article == string("c") || article == string("h")) {
            basetax = 0;
        } 
        else if (article == string("m") || article == string("p")) {
            basetax = 10;
        }
        else if (article == string("ic") || article == string("ice")) {
            basetax = 5;
        }
        else if (article == string("ip") || article == string("ic") || article == string("ice") || article == string("ipe")) {
            basetax = 15; 
        }
        
        //Auswahl der Artikel und Berechnungen der Artikelpreise

        if (article == string("b")) {
            char book[40] = "book                                  ";
            cout << "How many? \n";                 //Anzahl des gewünschten Artikels eingeben
            cin >> anzahl;
            int anz = eingaber(anzahl,book);        //ungültige Eingaben abfangen
            if (anz == 0) {                         //Wird bei falscher Eingabe durchlaufen
                eingabef(anzahl);
            }
            tax_b = basetax;                        //Setzen des Steuersatzes
            summe_b = rech1(basetax, anzahl, b1);   //Berechnung des Preises incl. Steuer         
            anzeige(anzahl,tax_b,summe_b,book);     //Speichern in temporaere Datei
        }
        if (article == string("m")) { 
            char music[44] = "music                                    ";
            cout << "How many? \n";
            cin >> anzahl;
            int anz = eingaber(anzahl,music); 
            if (anz == 0) {
                eingabef(anzahl);
            }
            tax_m = anzahl * (m1 * basetax) / 100;
            summe_m = rech2(anzahl, tax_m, m1);
            anzeige(anzahl, tax_m, summe_m,music);
        }
        if (article == string("c")) { 
            char cb[45] = "chocolate bar                               ";
            cout << "How many? \n";
            cin >> anzahl;
            int anz = eingaber(anzahl,cb); 
            if (anz == 0) {
                eingabef(anzahl);
            }
            tax_c = basetax;
            summe_c = rech1(basetax, anzahl, c1);
            anzeige(anzahl, tax_b, summe_c, cb);            
        }
        if (article == string("ic")) {
            char ic[43] = "importet box of chocolate, price 10.00   ";
            cout << "How many? \n";
            cin >> anzahl;
            int anz = eingaber(anzahl,ic); 
            if (anz == 0) {
                eingabef(anzahl);
            }
            tax_ic = anzahl * (ic1 * basetax) /100;
            summe_ic = rech2(anzahl, tax_ic, ic1);
            anzeige(anzahl, tax_ic, summe_ic, ic);        
        }
        if (article == string("ice")) {
            char ice[39] = "importet box of chocolate, price 11.25";
            cout << "How many? \n";
            cin >> anzahl;
            int anz = eingaber(anzahl,ice); 
            if (anz == 0) {
                eingabef(anzahl);
            }
            tax_ice = anzahl * (ice1 * basetax) / 100;
            summe_ice = rech2(anzahl, tax_ice, ice1);
            anzeige(anzahl, tax_ice, summe_ice, ice);
        }
        if (article == string("ip")) {
            char ip[40] = "importet bottle of perfume, price 27.99";
            cout << "How many? \n";
            cin >> anzahl;
            int anz = eingaber(anzahl,ip); 
            if (anz == 0) {
                eingabef(anzahl);
            }
            tax_ip = anzahl * (ip1 * basetax) / 100;
            summe_ip = rech2(anzahl, tax_ip, ip1);
            anzeige(anzahl, tax_ip, summe_ip, ip);        
        }
        if (article == string("ipe")) {
            char ipe[40] = "importet bottle of perfume, price 47.50";
            cout << "How many? \n";
            cin >> anzahl;
            int anz = eingaber(anzahl,ipe); 
            if (anz == 0) {
                eingabef(anzahl);
            }
            tax_ipe = anzahl * (ipe1 * basetax) / 100;
            summe_ipe = rech2(anzahl, tax_ipe, ipe1);
            anzeige(anzahl, tax_ipe, summe_ipe, ipe);
        }
        if (article == string("p")) {
            char p[41] = "bottle of perfume                      ";
            cout << "How many? \n";
            cin >> anzahl;
            int anz = eingaber(anzahl,p); 
            if (anz == 0) {
                eingabef(anzahl);
            }
            tax_p = anzahl * (p1 * basetax) / 100;
            summe_p = rech2(anzahl, tax_p, p1);
            anzeige(anzahl, tax_p, summe_p, p);
        }
        if (article == string("h")) {
            char h[43] = "packet of headache pills              ";
            cout << "How many? \n";
            cin >> anzahl;
            int anz = eingaber(anzahl,h); 
            if (anz == 0) {
                eingabef(anzahl);
            }
            tax_h = basetax;
            summe_h = rech1(basetax, anzahl, h1);
            anzeige(anzahl, tax_h, summe_h, h);       
        }
    

} while (article != string("end")); //Ende des Einkaufs durch Eingabe von "end"


//Ausgabe der Gesamtsteuer und des Gesamtpreises

if (article == string("end")); {
    cout << "\n";
    //Ausgabe der Ueberschriften auf der Rechnung
    cout << "Quantity\t Article \t\t\t\t\t\t Price \t Tax \n";

    //Berechnung der Gesamtsteuer und des Gesamtpreises
    double tax_ges = tax_b + tax_m + tax_c + tax_ic + tax_ip + tax_p + tax_h + tax_ice + tax_ipe;
    double summe_ges = summe_b + summe_m + summe_c + summe_ic + summe_ip + summe_p + summe_h + summe_ice + summe_ipe;

    //Schreiben in Datei
    of_schreiben.open(s_data.c_str(), ios::app);
    of_schreiben << "Total \n";
    of_schreiben << summe_ges << "\n";
    of_schreiben << "Sales Taxes \n";
    of_schreiben << tax_ges << " ";
    of_schreiben.close();
}

//Aus Datei lesen und Bildschirmausgabe

string s;
if_lesen.open(s_data.c_str(), ios::in);         //Datei öffnen
while (!if_lesen.eof()) {                       //Solange noch Daten in Datei vorhanden
    getline(if_lesen, s);                       //Lese Zeile in Datei
    cout << s << endl;                          //Ausgabe der Zeile auf dem Bildschirm
}
if_lesen.close();                               //Datei schliessen

of_schreiben.open(s_data.c_str(), ios::trunc);  //Datei öffnen und leeren
of_schreiben.close();                           //Datei schliessen

remove("art.txt");                              //geleerte Datei löschen

return 0;
}
    

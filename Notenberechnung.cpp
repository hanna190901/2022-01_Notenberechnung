// Belegaufgabe//

/*
Die Berechnung der Bachelornote
Alle Lehrveranstaltungen (LV) eines Studiums sind thematisch in Module eingeteilt und erhalten je nach Schwierigkeit und Umfang der Aufwendungen eine Gewichtung (LP). 

Eine Modulnote wird aus den einzelnen Noten der LV unter Beachtung der jeweiligen Gewichtung wie folgt berechnet: Alle Noten werden mit ihrer Gewichtung multipli- 
ziert. Aus den jeweiligen Produkten wird eine Summe gebildet, die dann durch die Summe aller Gewichtungen geteilt die Modulnote ergibt. Außerdem ist zu beachten, dass 
die Modulnote nach dem Komma nur 1 Stelle besitzt (es wird nicht gerundet). 

Die Berechnung der Bachelornote (Gesamtnote f¨ur das Studium) erfolgt ¨aquivalent und ergibt sich unter Beachtung der Gesamtgewichtung des Moduls aus den Mo- 
dulnoten. Auch die Bachelornote besitzt nur 1 Kommastelle. Sie wird außerdem als Wortnote angegeben.

Jede Note und ihre Gewichtung bilden eine Einheit. Erzeugen und verwenden Sie zur Abbildung dieses Sachverhalts einen neuen Datentyp. Die zu verarbeitenden Daten sind 
zun¨achst aus einer Datei einzulesen. Der Dateiname wird vom Nutzer einge- geben (maximal 30 Zeichen). Anschließend werden die Modulnoten (mit Auflistung der Noten und 
LP aller jeweiligen LV) und die Gesamtnote ¨ubersichtlich angeordnet ausgegeben. 

Zur Vereinfachung k¨onnen Sie davon ausgehen, dass es maximal 10 Module geben kann und, dass in einem Modul maximal 15 LV enthalten sein k¨onnen. 

F¨ur den Fall, dass eine LV mit 5.0 bewertet wurde, gilt die LV als nicht bestanden und muss wiederholt werden. In dem Fall ist die Berechnung der Modulnote nicht 
m¨oglich. Das Modul wird in der Berechnung der Gesamtnote nicht betrachtet. 

Zum Test Ihres Programms stehen Ihnen verschiedene Dateien zur Verf¨ugung. Die Dateien haben folgenden Dateiaufbau: Der erste Wert gibt an, wie viele Module in der 
Datei enthalten sind. Danach folgen in exakter Menge die Anzahlen der LV in den Modulen. Anschließend werden alle Noten mit ihrer jeweiligen Gewichtungen paarweise 
aufgelistet. Zuletzt enth¨alt die Datei die korrekte L¨osung f¨ur die Modul- noten und die Bachelornote.
*/

#include <iostream>
#include <fstream>
using namespace std;

int main()
{
                                                                    // ÖFFNEN DER DATEI
    cout << "Geben Sie hier bitte Ihren Dateiname ein (Form: name.txt): ";
    string name;
    cin >> name;
    ifstream fin (name);

                                                                    // Fehlerüberprüfung
     if(!fin)
    {
       cout << "Datei konnte nicht geoeffnet werden!" << endl;
       return 0;
    }

                                                                    // DATEN EINLESEN
    int modulmenge;                         // max. 10              // Daten in Modulmenge speichern
    fin >> modulmenge;

    int lehrveranstaltungen [modulmenge];   // max. 15              // Daten in Lehrveranstaltungen speichern
    for (int j=0; j<modulmenge; j++)
        {fin >> lehrveranstaltungen[j];}

    struct noten                                                    // Noten initialisieren
    {
        float notenwert [10][15] = {{0}};
        int gewichtung [10][15] = {{0}};
    };
    noten meineNoten;
    for (int i=0; i<modulmenge; i++)                                // Daten in Noten speichern
    {
        for (int j=0; j<lehrveranstaltungen[i]; j++)
        {
            fin >> meineNoten.notenwert[i][j];
            fin >> meineNoten.gewichtung [i][j];
        }
    }

                                                                    // VARIABLEN INITIALISIEREN
    bool nicht_bestandene_LV = false;
    float modulnote[modulmenge]  = {0};
    int modulnote10[modulmenge]  = {0};
    int modulgewichtung[modulmenge]  = {0};
    float gesamtnote = 0;
    int gesamtnote10 = 0;
    int gesamtgewichtung = 0;
    string wortnote = " ";

                                                                    // RECHNUNG
    for (int i=0; i<modulmenge; i++)                                // einzelne Module durchlaufen
    {
        for (int j=0; j<lehrveranstaltungen[i]; j++)                // einzelne Lehrveranstaltungen durchlaufen
        {
            if (meineNoten.notenwert[i][j] == 5)                    // nichtbestandene Lehrveranstaltungen aussortieren
            {
                nicht_bestandene_LV = true;
            }
            else                                                    // Berechnung der Summen der Modulnote
            {
                modulnote[i] += (meineNoten.notenwert[i][j] * meineNoten.gewichtung[i][j]);
                modulgewichtung[i] += meineNoten.gewichtung[i][j];
            }
        }

        if (nicht_bestandene_LV)                                    // nichtbestandene Lehrveranstaltungen aussortieren
        {
            nicht_bestandene_LV = false;
        }
        else
        {
            modulnote[i] /= modulgewichtung[i];                     // Berechnung der Modulnote
            modulnote10[i] = modulnote[i] *10;                      // Kürzen auf eine Nachkommastelle
            modulnote[i] = modulnote10[i] * 0.1;

            gesamtnote += (modulnote[i] * modulgewichtung[i]);      // Berechnung der Summen der Gesamtnote
            gesamtgewichtung += modulgewichtung[i];
        }
    }

    gesamtnote /= gesamtgewichtung;                                 // Berechnung der Gesamtnote
    gesamtnote10 = gesamtnote *10;                                  // Kürzen auf eine Nachkommastelle
    gesamtnote = gesamtnote10 * 0.1;


    if (1.0 <= gesamtnote && gesamtnote <= 1.5)                     // Bestimmung der Wortnote
        {wortnote = "sehr gut";}
    else
    {
        if (1.6 <= gesamtnote && gesamtnote <= 2.5)
           {wortnote = "gut";}
        else
        {
            if (2.6 <= gesamtnote && gesamtnote <= 3.5)
                {wortnote = "befriedigend";}
            else
            {
                if (3.6 <= gesamtnote && gesamtnote <= 4.0)
                    {wortnote = "ausreichend";}
                else
                {
                    if (4.1 <= gesamtnote)
                        {wortnote = "nicht ausreichend";}
                    else
                        {cout << "Bei der Bestimmung der Wortnote trat ein Fehler auf." << endl;}
                }
            }
        }
    }


                                                                    // AUSGABE
    for (int i=0; i<modulmenge; i++)
    {
        cout << endl << "Noten der Lehrveranstaltungen des Moduls " << (i+1) << ": " << endl;

        for (int j=0; j<lehrveranstaltungen[i]; j++)                // Noten der Lehrveranstaltungen
        {
                cout << "LV " << (j+1) << ": " << meineNoten.notenwert[i][j] << " mit der Gewichtung " << meineNoten.gewichtung[i][j] << endl;

                if (meineNoten.notenwert[i][j] == 5)                // nichtbestandene Lehrveranstaltungen
                {
                    cout << "Lehrveranstaltung " << (j+1) << " aus Modul " << (i+1) << " wurde nicht bestanden und muss wiederholt werden." << endl;
                    nicht_bestandene_LV = true;
                }
        }

        if (nicht_bestandene_LV)                                    // Modulnoten
        {
            cout << "Modulnote fuer Modul " << (i+1) << ": " << "Keine Berechnung moeglich, eine Lehrveranstaltung wurde nicht bestanden." << endl;
            nicht_bestandene_LV = false;
        }
        else
            cout << "Modulnote fuer Modul " << (i+1) << ": " << modulnote[i] << " mit der Gewichtung " << modulgewichtung[i] << endl;
    }

                                                                    // Gesamtnote
    cout << endl << "Als Gesamtnote ergibt sich " << gesamtnote << ". Das ist " << wortnote << "." << endl;

    return 0;
}

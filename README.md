Laboratoorse töö ülesandeks on kirjutada 6 järgmist funktsiooni: 
4.2.1. Esimene funktsioon 
void PrintObjects(HeaderC *pStruct4);  
Sisendparameetriks on viit lähtestruktuuri esimesele sidujale. Funktsiooni ülesandeks on 
väljastada kõikide struktuuris paiknevate objektide kirjeldused (iga objekt eraldi reas). 
Väljastavaks funktsiooniks on printf. Väljastamise formaatimise string (printf esimene 
parameeter) on toodud failis Objects.h.  
See funktsioon tuleb kirjutada kõige esimesena, sest ilma temata ei ole võimalik 
ülejäänud funktsioonide tööd kontrollida. 
4.2.2. Teine funktsioon 
int InsertNewObject(HeaderC **pStruct4, char *pNewID, int NewCode); 
Sisendparameetriteks on viit viidale, mis omakorda viitab esimesele olemasolevale 
HeaderC tüüpi sidujale; viit uue objekti identifikaatorile ja uue objekti kood. Funktsiooni 
ülesandeks on luua uus objekt ja lülitada ta andmestruktuuri. 
Funktsioon peab esmalt kontrollima, kas uus identifikaator ikka vastab eespool toodud 
formaadile. Kui see tingimus ei ole täidetud, väljastab funktsioon lihtsalt nulli. Edasi 
peab funktsioon kontrollima, kas sellise identifikaatoriga objekt ikka tõesti puudub. Kui 
ta on olemas, väljastab funktsioon samuti lihtsalt nulli. Kui sellise identifikaatoriga 
objekti ei ole, tuleb ta luua ning lülitada õigesse ahelloendisse. Kõik vajalikud mäluväljad 
20 
tuleb funktsiooni malloc abil tellida. Ka identifikaatori jaoks on vaja omaette mäluvälja, 
kuhu sisendparameetriks olev string tuleb kopeerida. Kellaaeg või kuupäev tuleb lugeda 
arvuti kellalt ja teisendada (vastavad funktsioonid on objektmoodulis DateTime.obj,  
prototüübid on failis DateTime.h). Uue objekti asukoht oma ahelloendis ei ole oluline. 
Kui funktsioon täitis oma ülesande, väljastab ta suuruse 1. 
Võib juhtuda, et etteantud uue identifikaatori esimese sõna algustähega objekte varem ei 
olnudki ja seetõttu puudub ka vastav siduja. Sellisel juhul tuleb puuduv siduja kõigepealt 
luua ja paigutada ta sidujate ahelloendis ettenähtud kohale. Samuti tuleb luua viitade 
vektor ja täita ta nullidega. Kui uus HeaderC tüüpi siduja tuleb kõige esimeseks, siis 
muutub ka viit struktuuri algusele. Seetõttu on viit struktuuri algusele nii 
sisendparameeter  kui ka väljundparameeter. 
Funktsiooni katsetades proovige kindlasti läbi järgmised olukorrad: 
1. Uus objekt tuleb juba olemasolevasse ahelloendisse. 
2. Sellise esimese sõna algustähega objekte siiani ei olnud, mistõttu puudub ka vajalik 
HeaderC siduja ja viitade vektor: 
a. Uus siduja tuleb HeaderC ahelloendis kõige esimeseks. 
b. Uus siduja tuleb HeaderC ahelloendis kõige viimaseks. 
c. Uus siduja tuleb HeaderC ahelloendis kusagile keskele. 
3. Sellise esimese sõna algustähega objekte küll oli, kuid teise sõna algustähega objekte 
mitte. 
4. Uue objekti identifikaator on ebaõiges formaadis. 
5. Uue objekti identifikaator on sama mis mõnel juba olemasoleval objektil. 
4.2.3. Kolmas funktsioon 
Objectn* RemoveExistingObject(HeaderC **pStruct4, char *pExistingID); 
Objectn asemel tuleb kirjutada loomulikult Object1,  Object2  jne. Sisendparameetriteks 
on viit viidale, mis omakorda viitab esimesele olemasolevale HeaderC tüüpi sidujale ja 
viit 
stringile, mis peab kokku langema ühe eeldatavalt olemasoleva objekti 
identifikaatoriga. Funktsiooni ülesandeks on leida see objekt ja eemaldada ta 
andmestruktuurist. Eemaldatud objekti kustutada ei tohi. Väljundsuuruseks on viit 
eemaldatud objektile. Kui objekti ei leitud, on väljundsuuruseks null. 
Võib juhtuda, et eemaldatav objekt on oma ahelloendis ainuke olemasolev ning rohkem 
sama esimese sõna algustähega objekte pole. Sellisel juhul tuleb pärast objekti 
eemaldamist eemaldada ning kustutada nii tema algustähele vastav HeaderC tüüpi siduja 
kui ka sellega seotud viitade vektor. Kui näiteks Vaher Peeter on ainukene objekt, mille 
esimene sõna algab ‘V’ tähega, siis selle eemaldamisega koos tuleb eemaldada ka veel 
tähele ‘V’ vastav HeaderC koos viitade vektoriga. 
Kui kustutatud HeaderC tüüpi siduja oli kõige esimene, siis muutub ka viit struktuuri 
algusele. Seetõttu on viit struktuuri algusele nii sisendparameeter  
väljundparameeter.  
Funktsiooni katsetades proovige kindlasti läbi järgmised olukorrad: 
1. Eemaldatav objekt paikneb ahelloendis, kus on rohkem kui üks lüli: 
a. Eemaldatav objekt on oma ahelloendis esimene.   
kui ka 
21 
b. Eemaldatav objekt on oma ahelloendis viimane. 
c. Eemaldatav objekt on oma ahelloendis kusagil keskel. 
2. Eemaldatav objekt on oma ahelloendis ainukene, kuid sama esimese sõna esitähega 
objekte on rohkem, mistõttu HeaderC tüüpi siduja jääb alles. 
3. Eemaldatav objekt on oma ahelloendis ainukene ja sama esimese sõna esitähega 
objekte rohkem ei ole, mistõttu HeaderC tüüpi siduja kaob: 
a. Kustutatav HeaderC siduja on ahelloendis kõige esimene. 
b. Kustutatav HeaderC siduja on ahelloendis kõige viimane. 
c. Kustutatav HeaderC siduja on ahelloendis kusagil keskel. 
4. Etteantud identifikaatoriga objekti ei ole olemas. 
4.2.4. Neljas funktsioon 
Node *CreateBinaryTree(HeaderC *pStruct4);  
Sisendparameetriks on viit lähtestruktuuri esimesele sidujale. Funktsiooni ülesandeks on 
ehitada kahendotsingu puu, mille tipud viitavad lähtestruktuuris olevatele kirjetele. 
Võtmeks on seejuures Objectn liige Code. Väljundparameetriks on viit puu juurtipule. 
Puu tippu esitav C struct on defineeritud failis Headers.h. 
Funktsioon peab olema mitterekursiivne, Tema kirjutamisel lähtuge slaidist "Kirje 
lisamine kahendpuule".  
4.2.5. Viies funktsioon 
void TreeTraversal(Node *pTree);  
Sisendparameetriks on viit neljanda funktsiooni poolt ehitatud puule. Funktsiooni 
ülesandeks on meetodil "vasak-juur-parem" käia läbi kõik puu tipud ja iga tipu puhul 
trükkida välja tema juurde kuuluva objekti kirjeldus (samuti nagu esimeses funktsioonis).  
Funktsioon peab olema mitterekursiivne, Tema kirjutamisel lähtuge slaidist "Puu läbikäik 
(3)". Magasiniga opereerimiseks kasutage vastavat C struct-i failist Headers.h ja võtke 
eeskujuks funktsioonide push ning pop koodid slaididelt "Näide magasini realisatsioonist 
(1)" ja "Näide magasini realisatsioonist (2)" 
4.2.6. Kuues funktsioon 
Node *DeleteTreeNode(Node *pTree, unsigned long int Code);  
Sisendparameetriks on viit neljanda funktsiooni poolt ehitatud puule ja võimalikule 
koodile. Funktsiooni ülesandeks on eemaldada puust tipp, mis viitab etteantud liiget Code 
sisaldavale objektile. Väljundparameetriks on viit pärast eemaldamist saadud puu 
juurtipule. 
Funktsioon peab olema mitterekursiivne. Tema kirjutamisel lähtuge slaididest "Kirje 
eemaldamine kahendpuust (1)" ja "Kirje eemaldamine kahendpuust (2)". 
Funktsiooni katsetades proovige kindlasti läbi järgmised olukorrad: 
1. Eemaldatav tipp on puu juureks. 
2. Eemaldataval tipul ei ole tütartippe. 
3. Eemaldataval tipul on ainult parempoolne tütartipp. 
4. Eemaldataval tipul on ainult vasakpoolne tütartipp. 
22 
5. Eemaldataval tipul on mõlemad tütartipud. 
6. Etteantud koodiga kirjet ei olegi. 

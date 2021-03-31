# LiepaajasAtklaataaOlimp2021 
> Uzdevums - izveidot spēli "Burtu jūklis". Liela izmēra tabulā ierakstīti Liepājas objektu nosaukumi; vienā rūtiņā ir viens burts. Spēlētājam jāatrod un jāizsvītro objektu nosaukumi. Spēles noslēgumā no neizsvītotajiem burtiem vai izsvītroto nosaukumu sākuma burtiem spēlētājam jāizveido nākamā apceļojamā objekta nosaukums (katram konkursa dalībniekam tas būs cits).
## Piezīme
Esam iekļāvuši jau nokompilētu programmu bin mapē.
Atliek tikai veikt dubultklikšķi uz bin\main.exe.
## Risinājuma darbības princips
Palaižot build.bat tiek nokompilēts pirmkods bin mapē, atvērta konsole un ielasīts objektu saraksts no places.config un puzles ģenerēšanas iestatījumi no puzzle.config, paturot meklējamo nākamo apceļojamo objektu kā noslēpumu, kurš, kārtējo reizi uzsākot konsoles lietojumprogrammu, nemainās. Konsolē tiek attēlota tabula, veidota no simboliem. Tabulas dati katrā reizē tiek randomizēti. Kad vārda sākuma un beigu koordinātes tiek uzminētas korekti,vārds tiek atzīmēts zaļā krāsā. Kad visi vārdi ir atzīmēti, tabulā tiek izcelti burti sarkanā krāsā, no kuriem jācenšas atminēt viens no Liepājas objektiem. Pēc spēles pabeigšanas laiks tiek pieglabāts rezultātu teksta failā results.txt kopā ar "timestamp", kad šis laiks tika sasniegts.
## Darbības vides prasības
- Operētājsistēma - Windows Vista vai jaunāka.
- Kompilēšanai:
  - C++11 kompilators
    - PATH env mainīgajam jāsatur ceļš uz mapi, kurā atrodas g++
  - Boost C++ bibliotēka
- Pēc iespējas lielāks monitors :D
## Pēc noklusējama apskatāmie objekti
- Spīķeris
- Raiņa parks
- Alpīnisma siena LOC Manēžā
- LOC Ledus  halle
- Latvijas lielākās bungas
- Stadions "Olimpija"
- Liepājas bāka
- Jūrmalas parka skeitparks
- Kristapa Porziņģa basketbola laukums
- Jaunākais viedais luksofors
- Viedais luksofors
- Stadions "Daugava"
- Liepājas Lutera baznīca
- Piemiņas zīme vācu filosofam Imanuelam Kantam
- Karostas cietums
- O.Kalpaka tilts
- Dzintara pulkstenis
- Skultpūra "Dzintara latvieši"
- Liepājas Universitāte
- Iekštelpu ekstrēmā sporta trase
- Zirgu salas dabas taka
- Skulptūra "Laivinieks"
- LOC Baseins SPA
- LOC Tenisa halle
- Bērnu rotaļu laukums Jūrmalas parkā
- Zinātnes un izglītības inovāciju centrs "ZIIC"
- Liepājas Latviešu biedrības nams
- Kultūras nams "Wiktorija"
- Liepājas leļļu teātris
- Liepājas muzejs
- Liepājas teātris
- Vecās ostmalas promenāde
- Vēja māte
- Jāņa Čakstes laukums
- Rožu laukums
- Juliannas pagalms
- Mūziķu slavas aleja
- Dabas māja
- Spoku koks
- Pētertirgus
- Nosaukums "Liepāja" pludmalē
- Romas dārzs
- Svētā Jāzepa katedrāle
- Svētā Trīsvienības katedrāle
��    g      T  �   �      �  N   �  `    	  �   a	  �   
  3  �
  y   �     A  	   O  }   Y  I   �     !  r   2     �     �     �     �  �     g   �  i   �  �   b  �   �  	   �     �     �  #   �     �  {   �    T     h     o     |     �     �     �  =   �       k     	   �     �  �   �     W     m     �  S   �  
   �     �     �               +  �   =     �  �   �  �   N  y     �   �  �     �   �  B   |     �  
   �     �     �     �             �   #                    0  �   7  A   �  *     R   B  V   �  
   �  �  �  l   x     �     �  �         �      �      �      �      �      �      �   z   !  �   !  2  
"    =#  �   T$    G%  �   g&  M   3'  �   �'  �   u(     V)    e)  {   i*  <  �*  �   ",  |   �,  �   &-  �   �-  �  �.  �   20     �0     �0  M   �0  N   31     �1  �   �1  ,   t2  -   �2  -   �2  '   �2  �   %3  �   �3     M4  �   �4  �   �5     Z6     k6     �6  %   �6  
   �6  �   �6  �  l7     :     :     !:  $   8:     ]:     }:  N   �:     �:  O   �:     I;     P;  �   _;     '<     ><     V<  p   ]<     �<     �<     �<     =     =     4=  �   J=     �=  �   �=    g>  r   i?  �   �?  �   �@  �   �A  F   =B     �B     �B     �B  $   �B     �B  '   �B     C  �   5C     5D     =D     DD     [D  �   kD  F   E  N   bE  h   �E  {   F     �F  �  �F  �   iH     �H  &   I  �   -I     �I     �I     �I     J     J     &J     AJ  �   WJ  �   �J  �  fK  �   �L  1  �M  �  O  �   �P  w   �Q  �   +R    S     T    +T  �   CU        I          1   O       M         e              3   G      ,   S       /   >   L          K          .   8             W   D      d       F   :   2   B       9   (       H       R   "           J   g   T   a   ]       7          0   &              _   Q       V   Y              [   ^   U   f   #              +      @   ?   <   %       !   N   5   b          \      4   ;            E   c                                           X   A   Z   )       *   C   	   P          '   6   `   =      
      -       $    0 means brush is transparent, 1 fully visible
(also known as alpha or opacity) A low value will make the direction input adapt more quickly, a high value will make it smoother Add a random offset to the position where each dab is drawn
 0.0 disabled
 1.0 standard deviation is one basic radius away
<0.0 negative values produce no jitter Add randomness to the mouse pointer; this usually generates many small lines in random directions; maybe try this together with 'slow tracking' Alter the radius randomly each dab. You can also do this with the by_random input on the radius setting. If you do it here, there are two differences:
1) the opaque value will be corrected such that a big-radius dabs is more transparent
2) it will not change the actual radius seen by dabs_per_actual_radius Angle by which elliptical dabs are tilted
 0.0 horizontal dabs
 45.0 45 degrees, turned clockwise
 180.0 horizontal again Anti-aliasing Ascension Aspect ratio of the dabs; must be >= 1.0, where 1.0 means a perfectly round dab. TODO: linearize? start at 0.0 maybe, or log? Basic brush radius (logarithmic)
 0.7 means 2 pixels
 3.0 means 20 pixels Change color hue Change color hue.
-0.1 small clockwise color hue shift
 0.0 disable
 0.5 counterclockwise hue shift by 180 degrees Change color lightness (HSL) Change color satur. (HSL) Change color satur. (HSV) Change color value (HSV) Change position depending on pointer speed
= 0 disable
> 0 draw where the pointer moves to
< 0 draw where the pointer comes from Change the color lightness (luminance) using the HSL color model.
-1.0 blacker
 0.0 disable
 1.0 whiter Change the color saturation using the HSL color model.
-1.0 more grayish
 0.0 disable
 1.0 more saturated Change the color saturation using the HSV color model. HSV changes are applied before HSL.
-1.0 more grayish
 0.0 disable
 1.0 more saturated Change the color value (brightness, intensity) using the HSV color model. HSV changes are applied before HSL.
-1.0 darker
 0.0 disable
 1.0 brigher Color hue Color saturation Color value Color value (brightness, intensity) Colorize Colorize the target layer, setting its hue and saturation from the active brush colour while retaining its value and alpha. Correct the nonlinearity introduced by blending multiple dabs on top of each other. This correction should get you a linear ("natural") pressure response when pressure is mapped to opaque_multiply, as it is usually done. 0.9 is good for standard strokes, set it smaller if your brush scatters a lot, or higher if you use dabs_per_second.
0.0 the opaque value above is for the individual dabs
1.0 the opaque value above is for the final brush stroke, assuming each pixel gets (dabs_per_radius*2) brushdabs on average during a stroke Custom Custom input Custom input filter Dabs per actual radius Dabs per basic radius Dabs per second Dabs to draw each second, no matter how far the pointer moves Declination Declination of stylus tilt. 0 when stylus is parallel to tablet and 90.0 when it's perpendicular to tablet. Direction Direction filter Do not modify the alpha channel of the layer (paint only where there is paint already)
 0.0 normal painting
 0.5 half of the paint gets applied normally
 1.0 alpha channel fully locked Elliptical dab: angle Elliptical dab: ratio Eraser Fast random noise, changing at each evaluation. Evenly distributed between 0 and 1. Fine speed Fine speed filter Fine speed gamma Gross speed Gross speed filter Gross speed gamma Hard brush-circle borders (setting to zero will draw nothing). To reach the maximum hardness, you need to disable Anti-aliasing. Hardness How far you have to move until the stroke input reaches 1.0. This value is logarithmic (negative values will not inverse the process). How fast you currently move. This can change very quickly. Try 'print input values' from the 'help' menu to get a feeling for the range; negative values are rare but possible for very low speed. How many dabs to draw while the pointer moves a distance of one brush radius (more precise: the base value of the radius) How much pressure is needed to start a stroke. This affects the stroke input only. Mypaint does not need a minimal pressure to start drawing. How slow the custom input actually follows the desired value (the one above). This happens at brushdab level (ignoring how much time has past, if brushdabs do not depend on time).
0.0 no slowdown (changes apply instantly) How slow the input fine speed is following the real speed
0.0 change immediately as your speed changes (not recommended, but try it) How slow the offset goes back to zero when the cursor stops moving Jitter Lock alpha Offset by speed Offset by speed filter Opacity Opacity linearize Opacity multiply Paint with the smudge color instead of the brush color. The smudge color is slowly changed to the color you are painting on.
 0.0 do not use the smudge color
 0.5 mix the smudge color with the brush color
 1.0 use only the smudge color Pressure Radius Radius by random Random Right ascension of stylus tilt. 0 when stylus working end points to you, +90 when rotated 90 degrees clockwise, -90 when rotated 90 degrees counterclockwise. Same as 'fine speed filter', but note that the range is different Same as 'fine speed gamma' for gross speed Same as above, but the radius actually drawn is used, which can change dynamically Same as fine speed, but changes slower. Also look at the 'gross speed filter' setting. Save color Set the custom input to this value. If it is slowed down, move it towards this value (see below). The idea is that you make this input depend on a mixture of pressure/speed/whatever, and then make other settings depend on this 'custom input' instead of repeating this combination everywhere you need it.
If you make it change 'by random' you can generate a slow (smooth) random input. Similar as above but at brushdab level (ignoring how much time has past, if brushdabs do not depend on time) Slow position tracking Slow tracking per dab Slowdown pointer tracking speed. 0 disables it, higher values remove more jitter in cursor movements. Useful for drawing smooth, comic-like outlines. Smudge Smudge length Smudge radius Stroke Stroke duration Stroke hold time Stroke threshold The angle of the stroke, in degrees. The value will stay between 0.0 and 180.0, effectively ignoring turns of 180 degrees. The pressure reported by the tablet, between 0.0 and 1.0. If you use the mouse, it will be 0.5 when a button is pressed and 0.0 otherwise. This changes the reaction of the 'fine speed' input to extreme physical speed. You will see the difference best if 'fine speed' is mapped to the radius.
-8.0 very fast speed does not increase 'fine speed' much more
+8.0 very fast speed increases 'fine speed' a lot
For very slow speed the opposite happens. This controls how fast the smudge color becomes the color you are painting on.
0.0 immediately update the smudge color (requires more CPU cycles because of the frequent color checks)
0.5 change the smudge color steadily towards the canvas color
1.0 never change the smudge color This defines how long the stroke input stays at 1.0. After that it will reset to 0.0 and start growing again, even if the stroke is not yet finished.
2.0 means twice as long as it takes to go from 0.0 to 1.0
9.9 and bigger stands for infinite This gets multiplied with opaque. You should only change the pressure input of this setting. Use 'opaque' instead to make opacity depend on speed.
This setting is responsible to stop painting when there is zero pressure. This is just a convention, the behaviour is identical to 'opaque'. This input slowly goes from zero to one while you draw a stroke. It can also be configured to jump back to zero periodically while you move. Look at the 'stroke duration' and 'stroke hold time' settings. This is a user defined input. Look at the 'custom input' setting for details. This modifies the radius of the circle where color is picked up for smudging.
 0.0 use the brush radius
-0.7 half the brush radius (fast, but not always intuitive)
+0.7 twice the brush radius
+1.6 five times the brush radius (slow performance) This setting decreases the hardness when necessary to prevent a pixel staircase effect.
 0.0 disable (for very strong erasers and pixel brushes)
 1.0 blur one pixel (good value)
 5.0 notable blur, thin strokes will disappear Tracking noise When selecting a brush, the color can be restored to the color that the brush was saved with.
 0.0 do not modify the active color when selecting this brush
 0.5 change active color towards brush color
 1.0 set the active color to the brush color when selected how much this tool behaves like an eraser
 0.0 normal painting
 1.0 standard eraser
 0.5 pixels go towards 50% transparency Project-Id-Version: MyPaint git
Report-Msgid-Bugs-To: 
POT-Creation-Date: 2012-12-28 19:12+0100
PO-Revision-Date: 2011-11-16 21:21+0100
Last-Translator: Gergely Aradszki
Language: hu
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Content-Transfer-Encoding: 8bit
Plural-Forms: nplurals=2; plural=(n != 1);
 A 0 azt jelenti, hogy az ecset átlátszó, az 1 pedig, hogy teljesen látható.
(Alpha-ként, vagy átlátszatlanságként is ismert) Alacsony értékeknél az irány bemenet sokkal gyorsabban alkalmazkodik, magas értékeknél viszont finomabb lesz a vonal. Véletlen eltolást ad minden egyes foltnak.
 0.0 nincsen eltolás
 1.0 a standard deviáció (szórási távolság) egy alap-sugárnyi
<0.0 negatív értékek használatakor nincsen szórás Véletlenszerűséget ad a kurzor mozgásához: ez általában kis, véletlenszerű irányokba induló vonalakat eredményez. Érdemes lehet kipróbálni a „Lassú követéssel” együtt. A sugár foltonként véletlenszerűen változik, hasonlóan ahhoz, mintha a  „Véletlenszerű bemenet szerint”  bemenetet használnád a sugár beállításánál.Az itteni beállítás két dologban tér el ettől:
1. Az átlátszatlanság érték úgy módosul, hogy a nagyobb foltok átlátszóbbak lesznek
2. Nem hat az „A foltok száma valódi sugaranként” által látott értékre Az elliptikus foltok döntésének szöge.
 0.0 vízszintes foltok
 45.0 45 fokos, óramutató járásával megegyezően döntött
 180 ez is vízszintes Élsimítás Irányszög A foltok átlóinak aránya; >= 1.0, ahol az 1.0 a tökéletes kört jelenti. Alap ecset-sugár (logaritmikus)
 A 0.7 2 pixelt jelent
 A 3.0 20 pixel jelent Árnyalat megváltoztatása A szín árnyalatát változtatja.
-0.1 kis mértékű, óramutató járásával megegyező irányú árnyalat-eltolás
 0.0 nincsen eltolás
 0.5 óramutató járásával ellentétes irányú, 180 fokos eltolás. Szín világosságának változtatása (HSL) Szín telítettségének változtatása (HSL) Szín telítettségének változtatása (HSV) Szín értékének változtatása (HSV) A pozíció változtatása a sebesség függvényében
= 0: kikapcsolva
> 0: a mozgás céljánál rajzol
< 0: a mozgás kiindulási pontjánál rajzol A szín világosságának (luminancia, fényerő) változtatása a HSL színmodell szerint.
-1.0 feketébb
 0.0 nincs változás
 1.0 fehérebb A szín telítettségének változtatása a HSL színmodell szerint.
-1.0 szürkébb
 0.0 nincs változtatás
 1.0 telítettebb A szín telítettségének változtatása a HSV színmodell szerint. A HSV változtatások a HSL előtt kerülnek alkalmazásra.
-1.0 szürkébb
 0.0 nincs változtatás
 1.0 telítettebb A szín értékének változtatása (világosság, intenzitás) a HSV színmodell szerint. A HSV változtatások a HSL előtt kerülnek alkalmazásra.
-1.0 sötétebb
 0.0 nincs változtatás
 1.0 világosabb Szín árnyalata Szín telítettsége Szín értéke Árnyalat (világosság, intenzitás) Színezés Színezze a célréteget, az aktív ecset alapján módosítva az árnyalatát és telítettségét, miközben az értéket és az átlátszóságot változatlanul hagyja. Az egymásra rajzolt foltok összemosásakor keletkező egyenetlenséget korrigálja. Ennek eredményeként lineáris, természetes nyomást kapsz, ha a nyomás az „Átlátszatlanság szorzás” -ra van állítva, ahogy általában lenni szokott. A 0.9 általános beállításként elfogadható, de állítsd inkább alacsonyabbra, ha az ecsetnek nagy a szórása, vagy magasabbra, ha a „Foltok száma másodpercenként”  magas.
0.0: a fenti átlátszatlanság érték az egyes foltokra vonatkozik
1.0 a fenti átlátszatlanság érték a végső ecsetvonásra vonatkozik, felételezve, hogy minden pixel „Foltok száma sugaranként” *2 foltot kap átlagosan Saját Saját bemenet Saját bemenet szűrő A foltok száma valódi sugaranként Foltok száma alap sugaranként Foltok száma másodpercenként A rajzolandó foltok száma másodpercenként, a megtett úttól függetlenül Dőlésszög A toll dőlésszöge. 0, ha a toll párhuzamos a táblával, 90, ha merőleges. Irány Irány szűrő Ne módosítsa a réteg alpha csatornáját (csak ott fessen, ahol már most is van festék)
 0.0 normál festés
 0.5 a festék fele normálisan kerül fel
 1.0 az alpha csatornát teljesen zárolja Elliptikus folt: szög Elliptikus folt: arány Radír Gyors, véletlenszerű zaj, ami minden lépés során változik. Egyenletes eloszlású, 0 és 1 között mozog. Finom sebesség Finom sebesség szűrő Finom sebesség gamma Durva sebesség Durva sebesség szűrő Durva sebesség gamma Kemény ecset-körvonal (0-ra állítva az ecset nem fog festeni). A maximális keménység eléréséhez ki kell kapcsolni az élsimítást. Keménység Milyen táv után lesz a bemeneti érték 1.0. Ez az érték logaritmikus.
(a negatív értékek nem fordítják meg a folyamatot) A pillanatnyi sebesség, ami nagyon gyorsan tud változni. Próbáld ki az „Ecset bemeneti értékeinek kiírását a „Súgó” menüben, és láthatod az érték tartományt. Negatív értékek ritkán, de előfordulhatnak, ha nagyon lassú a mozgás. Hány foltot rajzoljon ki, míg az ecset egy ecset-sugárnyit elmozdul (pontosabban: a sugár alapja a távolság) Mekkora nyomás szükséges a vonás elkezdéséhez. Csak az ecsetvonás bemenetre hat. A MyPaint-nek nincsen szüksége minimális nyomásra sem a rajzolás megkezdésekor. Milyen lassan követi a saját bemenet a kívánt értéket (a fentebb lévőt). Ez folt szinten működik, figyelmen kívül hagyva az időt, hacsak a foltok száma nem függ az időtől.
0.0 nincsen lassulás (a változásokat azonnal alkalmazza) Milyen lassan követi a finom sebesség bemenet a valós sebességet
A 0.0 érték azonnali változást eredményez, ahogy a sebességed változik (nem ajánlott, de próbáld csak ki). Milyen lassan tér vissza az eltolás 0-ra, miután a kurzor megállt. Szórás Alpha zárolása Eltolás sebesség szerint Eltolás a sebesség szűrő szerint Átlátszatlanság: Átlátszatlanság lineárissá tétele Átlátszatlanság szorzó Az elkenési színnel fest az ecset színe helyett. Az elkenési szín lassan arra a színre változik, mint amire éppen fest.
 0.0 ne használja az elkenési színt
 0.5 az elkenési- és az ecset-szín keverése
 1.0 csak az elkenési szín használata Nyomás Sugár Véletlenszerű sugár Véletlenszerű A toll irányszöge. 0, ha a toll előre mutat. +90, ha a a toll az óramutató járásával megegyező irányba 90°-kal elfordul; -90, ha ellenkező irányba fordul 90°-ot. Ugyanaz, mint a „finom sebesség szűrő” , de más a tartomány.  Ugyanaz, mint a „Finom sebesség gamma” , csak a „Durva sebesség”-nek Ugyanaz, mint a fölötte lévő, de a valós, rajzolt sugarat veszi alapul, ami dinamikusan változhat. Ugyanaz, mint a „finom sebesség” , csak lassabban változik. Érdemes megnézni a „durva sebesség szűrő” -t is. Szín mentése A „Saját bemenetet” erre az értékre állítja. Ha lelassul, efelé az érték felé közelíti (lásd lejjebb). Ez lehetővé teszi, hogy a bemenet a nyomás/sebesség/stb. keveréke legyen, majd a többi beállítást ettől függővé lehet tenni, anélkül, hogy ezt a kombinációt máshol is újra be kellene állítani.
Ha a „Véletlenszerű szerinti” változásra állítod, lassú (sima) véletlenszerű bemenetet tudsz létrehozni. Hasonló a felette lévőhöz, de folt-szinten. (Nem veszi figyelembe az eltelt időt, ha a foltok száma nem függ az időtől.) Lassú pozíció-követés Lassú pozíció-követés foltonként Csökkenti a kurzor követésének sebességét. A 0 kikapcsolja, a nagyobb értékek csökkentik a kurzor remegését. Hasznos lehet sima, képregényszerű vonalak rajzolásához. Elkenés Elkenés hossza Elkenés sugara Vonás Ecsetvonás hossza Ecsetvonás tartási ideje Ecsetvonási küszöb Az ecset szöge fokban. Az érték 0.0 és 180.0 között mozoghat, tehát a 180 fokos fordulást már figyelmen kívül hagyja. A tábla által közölt nyomásérték, 0.0 és 1.0 között. Ha egeret használsz, az egérgomb lenyomásakor ez 0.5 lesz, egyébként 0.0. Ez a beállítás a „finom sebesség” extrém fizikai sebességekre adott reakcióját változtatja meg. A különbség akkor érzékelhető a legjobban, ha a „finom sebesség” a Sugarat vezérli.
-8.0: a nagyon gyors változás kevésbé hat a „finom sebesség” -re
+8.0: a nagyon gyors változás erősebben hat a „finom sebesség” -re
Nagyon kis sebességeknél a hatás ellentétes. Milyen gyorsan veszi fel az elkenés azt a színt, amire éppen fest.
0.0 azonnal változzon (nagyobb a processzor-igénybevétel a gyakoribb színellenőrzés miatt)
0.5 fokozatosan veszi fel a színt az elkenés
1.0 soha nem változik Azt határozza meg, hogy az ecsetvonás bemeneti értéke milyen sokáig marad 1.0. Ezután visszaugrik 0.0-ra, és újból nőni kezd, még akkor is, ha az ecsetvonás még nem fejeződött be.
2.0 kétszer olyan hosszú, míg 0.0-tól 1.0-ig ér
9.9 és ennél nagyobb számok már a végtelent jelentik Az átlátszatlanság ezzel az értékkel lesz megszorozva. Ennek a beállításnak csak a nyomásbemenetét kell megváltoztatni. Ha szeretnéd, hogy az átlátszatlanság a sebességtől függjön, használd inkább az „átlátszatlanság”  beállítást.
Ez a beállítás felelős azért, hogy 0 nyomás esetén megszakadjon a rajzolás. Ez csak egy konvenció, a viselkedése megegyezik az „átlátszatlanság”  beállítással. Ez az érték az ecsetvonás közben 0-tól lassan 1-ig nő. Be lehet állítani úgy is, hogy periodikusan visszaugorjon 0-ra. Nézd meg az „ecsetvonás hossza”  és az „ecsetvonás tartási ideje” beállításokat! Ez egy felhasználó által meghatározott bemenet. Nézd meg a „saját bemenet”  beállításait a részletekért! Elkenéskor módosítja a színvétel sugarát.
 0.0 ecsetsugár használata 
-0.7 az ecset sugarának fele (gyors, de nem mindig intuitív)
+0.7 az ecset sugarának kétszerese
+1.6 az ecset sugarának ötszöröse (lassú) Ez a beállítás csökkenti a keménységet ha szükséges, hogy megakadályozza az élek lépcsősödését.
0.0 kikapcsolva (nagyon erős radírokhoz és pixelecsetekhez)
1.0 egy pixelnyi elmosás (ajánlott érték)
5.0 jelentős elmosás, a vékony vonalak eltűnnek Követési zaj Egy ecset kiválasztásakor a színt vissza lehet állítani arra a színre, amelyikkel korábban elmentetted.
 0.0 ne módosítsa az aktív színt az ecset kiválasztásakor
 0.5 a szín változtatása az ecset színe felé
 1.0 az aktív szín átállítása az ecset színére Mennyire fog ez az eszköz radírként viselkedni.
 0.0 sima festés
 1.0 radír
 0.5 a pixelek az 50%-os átlátszóság felé közelítenek 
######################################################                  
#            Proiect Microprocesoare                 #
#                                                    #
#                                                    #
######################################################

###### Echipa CCS:
- Clapa Adrian 
- Coratu Luca
- Stoica Alexandru

###### Materiale:
- Push Button Digital
- BCD

###### Cerinte:
[x] Modificarea unei valori numerice (0-F) afisate pe BCD prin intermediul actionarii butonului push. :tada:

[ ] Interfata grafica va reprezenta segmentele aprinse din cadrul BCD-ului in conformitate cu valoarea afisata.

[ ] Posibilitatea de schimbare a directiei de numarare a valorii afisate de BCD din interfata grafica. Actionarea unui buton grafic va produce incrementarea sau decrementarea numararii.



### BCD: 
![Sorry! Nu s-a putut incarca](https://s3.us-west-2.amazonaws.com/secure.notion-static.com/06ded70b-35fd-497f-8999-c67e646386c3/Untitled.png?X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Content-Sha256=UNSIGNED-PAYLOAD&X-Amz-Credential=AKIAT73L2G45EIPT3X45%2F20221113%2Fus-west-2%2Fs3%2Faws4_request&X-Amz-Date=20221113T195302Z&X-Amz-Expires=86400&X-Amz-Signature=7060c549ec674571672bd62712f6b8cbc6f0547fc03a623e0d0d74d08e2b8002&X-Amz-SignedHeaders=host&response-content-disposition=filename%3D"Untitled.png"&x-id=GetObject)

- Segment A: conectat la PTB0
- Segment B: conectat la PTB1
- Segment C: conectat la PTB2
- Segment D: conectat la PTB3
- Segment E: conectat la PTC2
- Segment F: conectat la PTC1
- Segment G: conectat la PTC9
- Conector ** + **: conectat la alimentare

### Push button:
![Button](https://raw.githubusercontent.com/DFRobot/DFRobotMediaWikiImage/master/Image/DFR0029.JPG)

- Verde: PTA12
- Rosu: VCC (alimentare 3V)
- Negru: GND

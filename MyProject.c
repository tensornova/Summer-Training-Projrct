#define west 1
#define south 0
int lg = west;
void show(int w, int s) {
    int wt = w / 10, wo = w % 10;
    int st = s / 10, so = s % 10;
    portc = 0xFF; portb = wt; rc0_bit = 0; delay_ms(5);
    portc = 0xFF; portb = wo; rc1_bit = 0; delay_ms(5);
    portc = 0xFF; portb = st; rc2_bit = 0; delay_ms(5);
    portc = 0xFF; portb = so; rc3_bit = 0; delay_ms(5);
    portc = 0xFF;
}
int display(int sec, int sw, int ss, int chk){
    int i, j, cw = sw, cs = ss;
    for(i = 0; i < sec; i++){
        for(j = 0; j < 15; j++){
            show(cw, cs);
            if(chk && !re0_bit) return 1;
        }
        if(cw) cw--;
        if(cs) cs--;
    }
    return 0;
}
void main(){
    adcon1 = 0x06;
    trisb = 0x00; trisc = 0x00;
    trisd = 0x00; trise = 0x03;
    portc = 0xFF; portd = 0x00;

    while(1){
        if(re0_bit){ // Auto Mode
            if(lg == south){
                portd = 0x11; // West: Red, South: yellow
                display(3, 0, 3, 0);
            }
            lg = west; portd = 0x0C; // West: green, South: Red
            if(display(20, 20, 23, 1)) continue;
            portd = 0x0A; // West: yellow, South: Red
            if(display(3, 3, 3, 0)) continue;
            lg = south; portd = 0x21; // West: Red, South: green
            if(display(12, 15, 12, 1)) continue;
            portd = 0x11; // West: Red, South: yellow
            if(display(3, 3, 3, 0)) continue;
        }
        else{ // Manual Mode
            if(re1_bit == west){
                if(lg == south){
                    portd = 0x11; // West: Red, South: yellow
                    display(3, 0, 3, 0);
                }
                portd = 0x0C; // West: green, South: Red
                portc = 0xFF; lg = west;
            }
            else{
                if(lg == west){
                    portd = 0x0A; // West: yellow, South: Red
                    display(3, 3, 0, 0);
                }
                portd = 0x21; // West: Red, South: green
                portc = 0xFF; lg = south;
            }
        }
    }
}
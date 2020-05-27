//define local variable(s) here.  Use static keyword to keep local, e.g:
//   static int i;  // defines a local int named i
static char earthquakeMagnitude = 0x00;
static char dTick = 0x00;


/*complete the state machine*/

void Detect_EQ()
{
    switch(detect_eq_state)
    {
        case DEQInit:
            //init variable(s) here.
            earthquakeMagnitude = PINA >> 3;
            detect_eq_state = DEQWait;
            break;

        case DEQWait:
            if(earthquakeMagnitude > 0){
                detect_eq_state = DEQDetect;
            }
            else{
                detect_eq_state = DEQWait;
            }
            break;

        case DEQDetect:
            if(earthquakeMagnitude > 0){
                detect_eq_state = DEQDetect;
            }
            else{
                dTick = 0;
                detect_eq_state = DEQEnd;
            }
            break;
        
        case DEQEnd:
            if(earthquakeMagnitude == 0 && dTick <= 10){
                
                detect_eq_state = DEQEnd;
            }
            else{
                detect_eq_state = DEQDetect;
            }

            if(dTick > 10){
                detect_eq_state = DEQWait;
            }
            break;

        default:
            detect_eq_state = DEQInit;
            break;
    }
    switch(detect_eq_state)
    {
        case DEQInit:
            break;

        case DEQWait:
            earthquakeMagnitude = PINA >> 3;
            detect = 0x00;
            break;

        case DEQDetect:
            earthquakeMagnitude = PINA >> 3;
            detect = 0x02;
            break;
        
        case DEQEnd:
            dTick++;
            earthquakeMagnitude = PINA >> 3;
            // detect = 0x00;
            break;

        default:
            earthquakeMagnitude = PINA >> 3;
            break;
    }
}

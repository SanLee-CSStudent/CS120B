
//define local variable(s) here.  Use static keyword to keep local, e.g:
//   static int i;  // defines a local int named i
static char first = 0x00;
static char second = 0x00;

/*complete the state machine*/

void Detect_ZC()
{
    switch(detect_zc_state)
    {
        case DZCInit:
            detect_zc_state = DZCWait;
            break;
        
        case DZCWait:
            if(detect){
                detect_zc_state = firstSample;
            }
            else{
                detect_zc_state = DZCWait;
            }
            break;  

        case firstSample:
            detect_zc_state = secondSample;
            break;

        case secondSample:
            if(!detect){
                detect_zc_state = DZCWait;
            }
            else{
                detect_zc_state = firstSample;
            }

            break;

        default:
            detect_zc_state = DZCInit;
            break;
    }
    switch(detect_zc_state)
    {
        case DZCInit:
            break;

        case firstSample:
            first = PINA & 0x07;
            zerocross = 0x00;
            break;

        case secondSample:
            second = PINA & 0x07;
            
            if(((first >> 2) != (second >> 2)) && ((first & 0x03) == (second & 0x03))){
                zerocross = 0x04;
            }
            else{
                zerocross = 0x00;
            }

            break;

        default:
            break;
    }
}

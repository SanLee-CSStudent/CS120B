
//define local variable(s) here.  Use static keyword to keep local, e.g:
//   static int i;  // defines a local int named i

/* complete the state machine. */

void Detect_Max_Amp()
{
    switch(detect_max_amp_state)
    {
        case DMAInit:
            detect_max_amp_state = DMAWait;
            break;
        
        case DMAWait:
            if(detect){
                detect_max_amp_state = DMADetect;
            }
            else{
                detect_max_amp_state = DMAWait;
            }
            break;

        case DMADetect:
            if(!detect){
                detect_max_amp_state = DMAWait;
            }
            else{
                detect_max_amp_state = DMADetect;
            }
            break;

        default:
            break;
    }
    switch(detect_max_amp_state)
    {
        case DMAInit:
            break;

        case DMAWait:
            amplitude = 0x00;
            break;

        case DMADetect:
            amplitude = (PINA >> 3) << 3;
            break;
        
        default:
            break;
    }
}

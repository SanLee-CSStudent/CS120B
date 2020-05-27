
//define local variable(s) here.  Use static keyword to keep local, e.g:
//   static int i;  // defines a local int named i
static unsigned char pTick = 0x00;


/*complete the state machine*/

void Ping()
{
    switch(ping_state)
    {
        case PInit:
            ping_state = PHigh;
            break;

        case PHigh:
            if(pTick > 1){
                pTick = 0;
                ping_state = PLow;
            }
            else{
                ping_state = PHigh;
            }
            break;

        case PLow:
            if(pTick > 9){
                pTick = 0;
                ping_state = PHigh;
            }
            else{
                ping_state = PLow;
            }
            break;

        default:
            ping_state = PInit;
            break;
    }
    switch(ping_state)
    {
        case PInit:
            break;

        case PHigh:
            pingActive = 0x01;
            pTick += 1;
            break;

        case PLow:
            pingActive = 0x00;
            pTick += 1;
            break;

        default:
            break;
    }
}

#include "../../headers/cpu.h"

static int claim = 0;

void SortTargets(void)
{
     int i;
     char swapped = 1;
     while (swapped)
     {
         swapped = 0;
         for (i = 0; i < GatewayCount - 1; i++)
         {
             char condition1 = gateways[i]->priority < gateways[i + 1]->priority;
             char condition2 = gateways[i]->priority == gateways[i + 1]->priority;
             char condition3 = gateways[i]->id > gateways[i + 1]->id;
             if (condition1 || (condition1 && condition2))
             {
                 Gateway* temp = gateways[i + 1];
                 gateways[i + 1] = gateways[i];
                 gateways[i] = temp;
                 swapped = 1;
             }
         }
     }
}

void UpdatePending()
{
    if (MousePending())
    {
        gateways[Mouse]->IP = 1;
    }
    if (KeyboardPending())
    {
        gateways[Keyboard]->IP = 1;
    }
}

void InitPLIC(void)
{
    // initalize all targets
    SortTargets();
    UpdatePending();
}

void FindPending(Target* t)
{
    int i = 0;
    for (; i < GatewayCount; i++)
    {
        if(t->IE[i])
        {
            if (gateways[i]->priority > t->threshold)
            {
                if(gateways[i]->IP)
                {
                    claim = gateways[i]->id;
                    ChangeBit(t->s->csr[mip], 1, t->privilege);
                    return;
                }
            }
        }
    }
}

void Operate(void)
{
    int i;
    for (i = 0; i < TargetCount; i++)
    {
        FindPending(targets[i]);
    }
}

int Claim(Target t)
{
    return claim;
}

void Complete(int irq)
{
    int i;
    for (int i = 0; i < GatewayCount; i++)
    {
        if (gateways[i]->id == irq)
        {
            gateways[i]->IP ^= gateways[i]->IP;
        }
    }
}


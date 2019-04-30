Data Structure
==============

Queue with getmin
-----------------

| Given a long list of positive integers
| Output the minimum value of the latest 10000 inputs
| i.e. When the 10001th input comes, the 1st input is discarded and will not be considered in finding the minimum value.

.. code-block:: cpp

    int input;
    int cnt = 1;

    while(cin >> input && cin){
        if (cnt++ > 10000)
            dq();
        enq(input);
        cout << getMin() << "\n";
    }

.. code-block:: cpp

    struct node {
        int num;
        int min;
    };

    node stackIN[maxn];
    node stackOUT[maxn];

    int in=0;
    int ot=0;

    int getMin(){
        if(in > 0 && ot > 0)
            return min(stackIN[in-1].min, stackOUT[ot-1].min);
        if(ot==0) {
            int newMin = stackIN[in-1].num;
            while(in!=0){
                    if(stackIN[in-1].num<newMin) newMin = stackIN[in-1].num;
                    stackOUT[ ot++ ] = (node){stackIN[ in-1 ].num,newMin};
                    in--;
                }
            return stackOUT[ot-1].min;
        }
        return -1; // if return -1, something wrong
    }

    void enq(int i){
        if(in == 0)
            stackIN[in++] = (node){i, i};
        else{
            int eh = min(i,stackIN[in-1].min);
            stackIN[in++] = (node){i, eh};
        }
    }

    void dq(){
        if(ot==0){
            int newMin = stackIN[in-1].num;
            while(in!=0){
                    if(stackIN[in-1].num<newMin)
                        newMin = stackIN[in-1].num;
                    stackOUT[ot++] = (node){stackIN[in-1].num,newMin};
                    in--;
                }
        }
        ot--;
    }
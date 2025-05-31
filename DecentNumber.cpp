//Decent number
//55533333
void decentNumber(int n) {
    if(n == 0 || n ==1 || n==2 || n==4 || n== 7){
        cout << -1 << endl;
    }
    else if(n == 3 || n == 6){
        cout  << string(n, '5') << endl;
    }
    else if(n == 5){
        cout << string(5, '3') << endl;
    }
    else{
        int maxX = -1;  // To store the maximum value of x
        int maxY = -1;  // To store the corresponding y

        for (int y = 0; y <= n / 5; ++y) {  // y can range from 0 to 2
            if ((n - 5 * y) % 3 == 0) {  // Check if (n - 5y) is divisible by 3
                int x = (n - 5 * y) / 3;  // Calculate x
                if (x > maxX) {  // Maximize x
                    maxX = x;
                    maxY = y;
                }
            }
        }

        if (maxX == -1) {
            cout << "-1" << endl;
        } else {
            cout << string(maxX*3, '5') << string(maxY*5, '3')<< endl;
        }
    }
}
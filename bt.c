#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

int main(){
    struct sockaddr_rc addr = { 0 };
    int s, status;
    char *dest =  "98:D3:31:F7:3B:D0"; //  HC05 = "98:D3:31:F7:3B:D0"

    s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

    addr.rc_family = AF_BLUETOOTH;
    addr.rc_channel = (uint8_t) 1;
    str2ba( dest, &addr.rc_bdaddr );

    status = connect(s, (struct sockaddr *)&addr, sizeof(addr));
    if( status < 0 ) perror("uh oh");
    while(1){
        char buf[1];
        recv(s, buf, 1, 0);
        printf("%s", buf);
        if(buf[0] == 'g'){
            system("google-chrome 'https://google.com' &");
        }
        else if(buf[0] == 'c'){
            system("cheese &");
        }
        else if(buf[0] == 'v'){
            system("code .");
        }
        else if(buf[0] == 'w'){
            system("whatsie &");
        }
        else if(buf[0] == 'n'){
            system("google-chrome 'https://www.netflix.com' &");
        }
    }
    close(s);
    return 0;
}

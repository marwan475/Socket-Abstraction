#include <winsock2.h>
#include <stdio.h>

WSADATA wsaData;

#define MAX_BUF 512

int main() {

  int iResult;
  SOCKET outsoc;
  SOCKADDR_IN outinfo, srcinfo;
  int destport = 8888;
  char destip[] = "192.168.1.20";
  char sendbuf[MAX_BUF]; 

  // Initialize Winsock
  iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
  if (iResult != 0) {
    printf("WSAStartup failed: %d\n", iResult);
    WSACleanup();
    return -1;
  }

  outsoc = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

  if (outsoc == INVALID_SOCKET){
    printf("Send Socket failed to be created\n");
    WSACleanup();
    return -1;
  }

  outinfo.sin_family = AF_INET;
  outinfo.sin_port = htons(destport);
  outinfo.sin_addr.s_addr = inet_addr(destip);

  printf("\nPlease, type your message: "); //Ask user for message
  fgets(sendbuf, sizeof(sendbuf), stdin); //Read user's input

  sendto(outsoc, sendbuf, MAX_BUF, 0 , (SOCKADDR *) &outinfo, sizeof(outinfo));

  closesocket(outsoc);

  WSACleanup();

	return 0;

}

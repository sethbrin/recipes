#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <libgen.h>
#include <errno.h>
#include <fcntl.h>

/* Flags for SPLICE and VMSPLICE.  */
# define SPLICE_F_MOVE    1 /* Move pages instead of copying.  */
# define SPLICE_F_NONBLOCK  2 /* Don't block on the pipe splicing
                                              (but we may still block on the fd
                                                           we splice from/to).  */
# define SPLICE_F_MORE    4 /* Expect more data.  */
# define SPLICE_F_GIFT    8 /* Pages passed in are a gift.  */

int main(int argc, char* argv[])
{
  if (argc <= 2)
  {
    printf("usage: %s ip_address port_number backlog\n", basename(argv[0]));
    return 1;
  }

  const char* ip = argv[1];
  int port = atoi(argv[2]);

  struct sockaddr_in address;
  bzero(&address, sizeof(address));
  address.sin_family = AF_INET;
  inet_pton(AF_INET, ip, &address.sin_addr);
  address.sin_port = htons(port);

  int sock = socket(PF_INET, SOCK_STREAM, 0);
  assert(sock >= 0);

  int ret = bind(sock, (struct sockaddr*)&address, sizeof(address));
  assert(ret != -1);

  ret = listen(sock, 5);
  assert(ret != -1);

  sleep(20);
  struct sockaddr_in client;
  socklen_t client_addr_length = sizeof(client);
  int connfd = accept(sock, (struct sockaddr*)&client, &client_addr_length);

  if (connfd < 0)
  {
    printf("errno is: %d\n", errno);
  }
  else
  {
    int pipefd[2];
    ret = pipe(pipefd);
    assert(ret != -1);
    ret = splice(connfd, NULL, pipefd[1], NULL, 32768, SPLICE_F_MORE|SPLICE_F_MOVE);
    assert(ret != -1);
    ret = splice(connfd, NULL, pipefd[0], NULL, 32768, SPLICE_F_MORE|SPLICE_F_MOVE);
    assert(ret != -1);
    close(connfd);
  }
  close(sock);

  return 0;
}

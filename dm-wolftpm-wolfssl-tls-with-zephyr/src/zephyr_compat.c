#include "zephyr_compat.h"

#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <zephyr/net/socket.h>

static struct hostent   gh_entry;
static char            *gh_aliases[1] = { NULL };
static char             gh_addr[sizeof(struct in_addr)];
static char            *gh_addr_list[2] = { gh_addr, NULL };
static char             gh_name[NI_MAXHOST];

struct hostent *gethostbyname(const char *name)
{
    struct zsock_addrinfo hints = {
        .ai_family = AF_INET,
        .ai_socktype = SOCK_STREAM,
    };
    struct zsock_addrinfo *res = NULL;

    if (name == NULL) {
        return NULL;
    }

    if (zsock_getaddrinfo(name, NULL, &hints, &res) != 0 || res == NULL) {
        return NULL;
    }

    const struct sockaddr_in *sin = (const struct sockaddr_in *)res->ai_addr;
    memcpy(gh_addr, &sin->sin_addr, sizeof(struct in_addr));
    strncpy(gh_name, name, sizeof(gh_name) - 1);
    gh_name[sizeof(gh_name) - 1] = '\0';

    gh_entry.h_name = gh_name;
    gh_entry.h_aliases = gh_aliases;
    gh_entry.h_addrtype = AF_INET;
    gh_entry.h_length = sizeof(struct in_addr);
    gh_entry.h_addr_list = gh_addr_list;

    zsock_freeaddrinfo(res);
    return &gh_entry;
}

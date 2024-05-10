#include <stdio.h>
#include <uci.h>


int main (int agrc, char *argv[]) {
    struct uci_package *pkg;
    struct uci_element *e;
    static struct uci_context *ctx;


    ctx = uci_alloc_context();
    uci_set_confdir(ctx, UCI_CONFDIR);

    if (NULL == (pkg = uci_lookup_package(ctx, "network"))) {
        printf("Not found network\n");
        uci_free_context(ctx);
        return 0;
    }

    // uci_load(ctx,"network", &pkg);

    uci_foreach_element(&pkg->sections, e) {
        struct uci_section *s = uci_to_section(e);
        printf("%s:%s: %d\n", e->name, s->type, s->anonymous);
    }

    uci_free_context(ctx);

    return 0;
}
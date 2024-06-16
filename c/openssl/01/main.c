#include <openssl/pem.h>

#include "devel.h"

#define PUB_KEY	"id_rsa.pub"
#define PRI_KEY "gwn_firmware_private"


// Digital Signature


EVP_MD_CTX *sign_init(const char *name, const char *kfile) {
	EVP_MD_CTX *ctx;
	const EVP_MD *md;
	FILE *file;
	EVP_PKEY *key;
	int ret;

	OpenSSL_add_all_digests();
	if (!(ctx = EVP_MD_CTX_create())) {
		error(-1, "Failed create CTX");
		return NULL;
	}

	if (!(md = EVP_get_digestbyname(name))) {
		error(-1, "Failed create Digest");
		return NULL;
	}

	if ((file = fopen(kfile, "r"))) {
		if(!(key = PEM_read_PrivateKey(file, NULL, NULL, NULL))) {
			fclose(file);
			error(0, "Failed init key");
			return NULL;
		}
		fclose(file);
	}

	/** Init EVP */
	if ((ret = EVP_DigestSignInit(ctx, NULL, md, NULL, key)) != 1) {
		error(ret, "Failed init EVP");
		return NULL;
	}

	return ctx;
}

int sign_update(EVP_MD_CTX *ctx, void *data, size_t dlen) {
	int ret;

	if ((ret = EVP_DigestSignUpdate(ctx, (void *)data, dlen)) != 1) {
		warning(0, "update error");
		return -1;
	}

	return 0;
}

int sign_finish(EVP_MD_CTX *ctx, void *sbuf, size_t *slen) {
	size_t len;

	EVP_DigestSignFinal(ctx, NULL, &len);
	if (sbuf && len <= *slen)
		EVP_DigestSignFinal(ctx, sbuf, slen);
	else
		return -1;

	return 0;
}

void sign_exit(EVP_MD_CTX *ctx) {
	return;
}

#define BUFIZE	1000
int main(int argc, char *argv[]) {
	EVP_MD_CTX *ctx;
	char buffer[BUFIZE + 1];
	FILE *file;
	size_t len = 1024;
	char *data, *buf;
	int ret, idx;
	int rlen;

	if (!argv[1])
		return 0;

	if (!(file = fopen(argv[1], "rb"))) {
		error(0, "Failed to open %s", argv[1]);
		return 0;
	}

	/** Init */
	if (!(ctx = sign_init("SHA1", PRI_KEY))) {
		error(0, "Failed to init digital sign");
		return 0;
	}

	/** Repare Data */
	idx = 0;
	memset(buffer, 0, sizeof(buffer));
	while ((rlen = fread(buffer, 1, BUFIZE, file))) {
		sign_update(ctx, buffer, rlen);
		memset(buffer, 0, sizeof(buffer));
	}

	/** Finish Data */
	buf = malloc(len);
	memset(buf, 0, len);
	sign_finish(ctx, buf, &len);
	debug("Sign Result: %d", len);
	hexdump(buf, len);

	/** */
	sign_exit(ctx);
	debug("Finished!");
	return 0;
}
#include <linux/init.h>
#include <linux/module.h>


#define MODNAME "Develop Crypto"


// ========================================================================= //
/*           ## skcipher: Symmetric Key Cipher Operation ##                  */

#include <crypto/skcipher.h>
#include <linux/scatterlist.h>

/* tie all data structures together */
struct skcipher_def {
    struct scatterlist sg;
    struct crypto_skcipher *tfm;
    struct skcipher_request *req;
    struct crypto_wait wait;
};

/* Perform cipher operation */
static unsigned int test_skcipher_encdec (struct skcipher_def *sk, int enc)
{
    int rc;

    if (enc)
        rc = crypto_wait_req(crypto_skcipher_encrypt(sk->req), &sk->wait);
    else
        rc = crypto_wait_req(crypto_skcipher_decrypt(sk->req), &sk->wait);

    if (rc)
		pr_info("skcipher encrypt returned with result %d\n", rc);

    return rc;
}

/* Initialize and trigger cipher operation */
static int test_skcipher (void)
{
    struct skcipher_def sk;
    struct crypto_skcipher *skcipher = NULL;
    struct skcipher_request *req = NULL;
    char *scratchpad = NULL;
    char *ivdata = NULL;
    unsigned char key[32];
    int ret = -EFAULT;

    skcipher = crypto_alloc_skcipher("cbc(aes)", 0, 0);
    if (IS_ERR(skcipher)) {
        pr_info("could not allocate skcipher handle\n");
        return PTR_ERR(skcipher);
    }

    req = skcipher_request_alloc(skcipher, GFP_KERNEL);
    if (!req) {
        pr_info("could not allocate skcipher request\n");
        ret = -ENOMEM;
        goto out;
    }

    skcipher_request_set_callback(req, CRYPTO_TFM_REQ_MAY_BACKLOG,
                      crypto_req_done,
                      &sk.wait);

    /* AES 256 with random key */
    get_random_bytes(&key, 32);
    if (crypto_skcipher_setkey(skcipher, key, 32)) {
        pr_info("key could not be set\n");
        ret = -EAGAIN;
        goto out;
    }

    /* IV will be random */
    ivdata = kmalloc(16, GFP_KERNEL);
    if (!ivdata) {
        pr_info("could not allocate ivdata\n");
        goto out;
    }
    get_random_bytes(ivdata, 16);

    /* Input data will be random */
    scratchpad = kmalloc(16, GFP_KERNEL);
    if (!scratchpad) {
        pr_info("could not allocate scratchpad\n");
        goto out;
    }
    get_random_bytes(scratchpad, 16);

    sk.tfm = skcipher;
    sk.req = req;

    /* We encrypt one block */
    sg_init_one(&sk.sg, scratchpad, 16);
    skcipher_request_set_crypt(req, &sk.sg, &sk.sg, 16, ivdata);
    crypto_init_wait(&sk.wait);

    /* encrypt data */
    ret = test_skcipher_encdec(&sk, 1);
    if (ret)
        goto out;

    pr_info("Encryption triggered successfully\n");

out:
    if (skcipher)
        crypto_free_skcipher(skcipher);
    if (req)
        skcipher_request_free(req);
    if (ivdata)
        kfree(ivdata);
    if (scratchpad)
        kfree(scratchpad);
    return ret;

	
}

// ========================================================================= //

#include <crypto/hash.h>


struct sdesc {
    struct shash_desc shash;
    char ctx[];
};

static struct sdesc *init_sdesc(struct crypto_shash *alg)
{
    struct sdesc *sdesc;
    int size;

    size = sizeof(struct shash_desc) + crypto_shash_descsize(alg);
    sdesc = kmalloc(size, GFP_KERNEL);
    if (!sdesc)
        return ERR_PTR(-ENOMEM);
    sdesc->shash.tfm = alg;
    //sdesc->shash.flags = 0x0;
    return sdesc;
}

static int calc_hash(struct crypto_shash *alg,
             const unsigned char *data, unsigned int datalen,
             unsigned char *digest)
{
    struct sdesc *sdesc;
    int ret;

    sdesc = init_sdesc(alg);
    if (IS_ERR(sdesc)) {
        pr_info("can't alloc sdesc\n");
        return PTR_ERR(sdesc);
    }

    ret = crypto_shash_digest(&sdesc->shash, data, datalen, digest);
    kfree(sdesc);
    return ret;
}

static int test_hash(const unsigned char *data, unsigned int datalen,
             unsigned char *digest)
{
    struct crypto_shash *alg;
    char *hash_alg_name = "sha1";
    int ret;

    alg = crypto_alloc_shash(hash_alg_name, CRYPTO_ALG_TYPE_SHASH, 0);
    if (IS_ERR(alg)) {
            pr_info("can't alloc alg %s\n", hash_alg_name);
            return PTR_ERR(alg);
    }
    ret = calc_hash(alg, data, datalen, digest);
    crypto_free_shash(alg);
    return ret;
}

// ========================================================================= //
/* rng cipher */

#include <crypto/rng.h>

static int get_random_numbers(u8 *buf, unsigned int len)
{
    struct crypto_rng *rng = NULL;
    char *drbg = "drbg_nopr_sha256"; /* Hash DRBG with SHA-256, no PR */
    int ret;

    if (!buf || !len) {
        pr_debug("No output buffer provided\n");
        return -EINVAL;
    }

    rng = crypto_alloc_rng(drbg, 0, 0);
    if (IS_ERR(rng)) {
        pr_debug("could not allocate RNG handle for %s\n", drbg);
        return PTR_ERR(rng);
    }

    ret = crypto_rng_get_bytes(rng, buf, len);
    if (ret < 0)
        pr_debug("generation of random numbers failed\n");
    else if (ret == 0)
        pr_debug("RNG returned no data");
    else
        pr_debug("RNG returned %d bytes of data\n", ret);

out:
    crypto_free_rng(rng);
    return ret;
}

// ========================================================================= //




// ========================================================================= //

// xfrm_crypto_test(struct sk_buff *skb) {



//     err = x->type->output(x, skb);





// }





// int esp_output_tail (struct xfrm_state *x, struct sk_buff *skb, struct esp_info *esp)
// {
// 	u8 *iv;
// 	int alen;
// 	void *tmp;
// 	int ivlen;
// 	int assoclen;
// 	int extralen;
// 	struct page *page;
// 	struct ip_esp_hdr *esph;
// 	struct crypto_aead *aead;
// 	struct aead_request *req;
// 	struct scatterlist *sg, *dsg;
// 	struct esp_output_extra *extra;
// 	int err = -ENOMEM;

// 	assoclen = sizeof(struct ip_esp_hdr);
// 	extralen = 0;

// 	if (x->props.flags & XFRM_STATE_ESN) {
// 		extralen += sizeof(*extra);
// 		assoclen += sizeof(__be32);
// 	}

// 	aead = x->data;
// 	alen = crypto_aead_authsize(aead);
// 	ivlen = crypto_aead_ivsize(aead);

// 	tmp = esp_alloc_tmp(aead, esp->nfrags + 2, extralen);
// 	if (!tmp)
// 		goto error;

// 	extra = esp_tmp_extra(tmp);
// 	iv = esp_tmp_iv(aead, tmp, extralen);
// 	req = esp_tmp_req(aead, iv);
// 	sg = esp_req_sg(aead, req);

// 	if (esp->inplace)
// 		dsg = sg;
// 	else
// 		dsg = &sg[esp->nfrags];

// 	esph = esp_output_set_extra(skb, x, esp->esph, extra);
// 	esp->esph = esph;

// 	sg_init_table(sg, esp->nfrags);
// 	err = skb_to_sgvec(skb, sg,
// 		           (unsigned char *)esph - skb->data,
// 		           assoclen + ivlen + esp->clen + alen);
// 	if (unlikely(err < 0))
// 		goto error_free;

// 	if (!esp->inplace) {
// 		int allocsize;
// 		struct page_frag *pfrag = &x->xfrag;

// 		allocsize = ALIGN(skb->data_len, L1_CACHE_BYTES);

// 		spin_lock_bh(&x->lock);
// 		if (unlikely(!skb_page_frag_refill(allocsize, pfrag, GFP_ATOMIC))) {
// 			spin_unlock_bh(&x->lock);
// 			goto error_free;
// 		}

// 		skb_shinfo(skb)->nr_frags = 1;

// 		page = pfrag->page;
// 		get_page(page);
// 		/* replace page frags in skb with new page */
// 		__skb_fill_page_desc(skb, 0, page, pfrag->offset, skb->data_len);
// 		pfrag->offset = pfrag->offset + allocsize;
// 		spin_unlock_bh(&x->lock);

// 		sg_init_table(dsg, skb_shinfo(skb)->nr_frags + 1);
// 		err = skb_to_sgvec(skb, dsg,
// 			           (unsigned char *)esph - skb->data,
// 			           assoclen + ivlen + esp->clen + alen);
// 		if (unlikely(err < 0))
// 			goto error_free;
// 	}

// 	if ((x->props.flags & XFRM_STATE_ESN))
// 		aead_request_set_callback(req, 0, esp_output_done_esn, skb);
// 	else
// 		aead_request_set_callback(req, 0, esp_output_done, skb);

// 	aead_request_set_crypt(req, sg, dsg, ivlen + esp->clen, iv);
// 	aead_request_set_ad(req, assoclen);

// 	memset(iv, 0, ivlen);
// 	memcpy(iv + ivlen - min(ivlen, 8), (u8 *)&esp->seqno + 8 - min(ivlen, 8),
// 	       min(ivlen, 8));

// 	ESP_SKB_CB(skb)->tmp = tmp;
// 	err = crypto_aead_encrypt(req);

// 	switch (err) {
// 	case -EINPROGRESS:
// 		goto error;

// 	case -ENOSPC:
// 		err = NET_XMIT_DROP;
// 		break;

// 	case 0:
// 		if ((x->props.flags & XFRM_STATE_ESN))
// 			esp_output_restore_header(skb);
// 	}

// 	if (sg != dsg)
// 		esp_ssg_unref(x, tmp);

// error_free:
// 	kfree(tmp);
// error:
// 	return err;
// }
// EXPORT_SYMBOL_GPL(esp_output_tail);




// static void aead_callback (struct crypto_async_request *base, int err) {
//     // struct sk_buff *skb = base->data;
// }
// //
// crypto_aead_test(char *name) {
//     struct crypto_aead *aead;
//     struct aead_request *req;
//     int err;

//     struct scatterlist *src_sg, *dst_sg;

//     //
//     aead = crypto_alloc_aead(name, 0, 0);

//     err = crypto_aead_setkey(aead, key, keylen);

//     err = crypto_aead_setauthsize(aead, icvlen);

//     req =   
    
//     /**/
//     kmalloc(len, GFP_ATOMIC);
//     PTR_ALIG        N(tmp, __alignof__(struct esp_output_extra));
//     //
//     aulen = crypto_aead_authsize(aead);
// 	ivlen = crypto_aead_ivsize(aead);

//     // Set Callback
//     aead_request_set_callback(req, 0, aead_callback, NULL);

//     //
//     aead_request_set_crypt(req, src_sg, dst_sg, len, iv);
    
//     //
//     aead_request_set_ad(req, assoclen);

//     //
//     memset(iv, 0, ivlen);
//     memcpy(iv + ivlen - min(ivlen, 8), (u8 *)&esp->seqno + 8 - min(ivlen, 8),
// 	       min(ivlen, 8));
    
//     //
//     err = crypto_aead_encrypt(req);
// }

// echainiv(safexcel-authenc-hmac-sha1-cbc-aes)

// int crypto_authenc_test (char *name, char *key, int klen) {
//     struct crypto_aead *aead;
//     struct rtattr *rta;
//     char *rkey, *p;
//     int rklen;
//     struct crypto_authenc_key_param *param;
    
//     //
//     aead = crypto_alloc_aead(name, 0, 0);

//     //
//     rklen = RTA_SPACE(sizeof(*param)) + klen;
//     rkey = kmalloc(rklen, GFP_KERNEL);
//     p = rkey;
//     rta = (void *)p;
//     rta->rta_type = CRYPTO_AUTHENC_KEYA_PARAM;
// 	rta->rta_len = RTA_LENGTH(sizeof(*param));
//     param = RTA_DATA(rta);
//     p += RTA_SPACE(sizeof(*param));

//     param->enckeylen = cpu_to_be32(klen);
//     memcpy(p, key, klen);

//     crypto_aead_setkey(aead, rkey, rklen);
    
    
//     //
//     aulen = crypto_aead_authsize(aead);
//     ivlen = crypto_aead_ivsize(aead);


//     err = crypto_aead_encrypt(req);
// }









static int devel_crypto_init (void)
{
	char data[] = "1213123421423532654356547564867867967745334253245464575467568765";
	char digest[512] = {0};

	printk(KERN_ALERT "load %s kernel module\n", MODNAME);

	test_skcipher();

	test_hash(data, strlen(data), digest);

	return 0;
}

module_init(devel_crypto_init);


static void devel_crypto_exit (void)
{
	printk(KERN_ALERT "remove %s kernel module\n", MODNAME);
}

module_exit(devel_crypto_exit);

MODULE_DESCRIPTION("This is a develp Kernel module");
MODULE_AUTHOR("Wenger Binning");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.0.0.1");



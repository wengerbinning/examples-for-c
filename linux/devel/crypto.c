#include <linux/init.h>
#include <linux/module.h>





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









static int cryptospeed_init(void)
{
	printk(KERN_ALERT "load crypto speed kernel module\n");
	return 0;
}

module_init(cryptospeed_init);


static void cryptospeed_exit(void)
{
	printk(KERN_ALERT "remove crypto speed kernel module\n");
}

module_exit(cryptospeed_exit);

MODULE_DESCRIPTION("This is a test crypto speed Kernel module");
MODULE_AUTHOR("Wenger Binning");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.0.0.1");






    #define __FLAGS_GET_FIELD(_flags, _type, _field) (((_type *)(_flags))->_field)
    #define _FLAGS_GET_ATTR(_flags, _type) __FLAGS_GET_FIELD(_flags, _type, attr)
    #define _FLAGS_GET_TYPE(_flags, _type) __FLAGS_GET_FIELD(_flags, _type, type)



typedef union flags {
    unsigned int values[1];
    struct {
        unsigned int attr: 16;
        unsigned int type: 8;
    };
} flags_t;

#define FLAGS_GET_ATTR(_flags) _FLAGS_GET_ATTR(_flags, flags_t)
#define FLAGS_SET_ATTR(_flags, _val)    (FLAGS_GET_ATTR(_flags) |= (_val))
#define FLAGS_CHECK_ATTR(_flags, _val) ((FLAGS_GET_ATTR(_flags) &  (_val)) && 1)
#define FLAGS_CLEAN_ATTR(_flags, _val)  (FLAGS_GET_ATTR(_flags) &=~(_val))

#define FLAGS_GET_TYPE(_flags) _FLAGS_GET_TYPE(_flags, flags_t)
#define FLAGS_SET_TYPE(_flags, _val)    (FLAGS_GET_TYPE(_flags)  = (_val))
#define FLAGS_CHECK_TYPE(_flags, _val)  (FLAGS_GET_TYPE(_flags) == (_val))

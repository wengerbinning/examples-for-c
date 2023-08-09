#ifndef __ASCII_H__
#define __ASCII_H__




#define ASCII_ID_CODE_MASK  0x000000FF


struct ascii_t {
    int id;
    char *name;
    char *caret;
    char *escape;
}





#define ASCII(id, name, caret, escape)

static struct ascii_t ascii_table = {
    /* Control Code */
    ASCII(0x00, "NULL", "^@",   "\\0"),
    ASCII(0x01, "SOH",  "^A",   ""),
    ASCII(0x02, "STX",  "^B",   ""),
    ASCII(0x03, "ETX",  "^C",   ""),
    ASCII(0x04, "EOT",  "^D",   ""),
    ASCII(0x05, "ENQ",  "^E",   ""),
    ASCII(0x06, "ACK",  "^F",   ""),
    ASCII(0x07, "BEL",  "^G",   "\\a"),
    ASCII(0x08, "BS",   "^H",   "\\b"),
    ASCII(0x09, "HT",   "^I",   "\\t"),
    ASCII(0x0A, "LF",   "^J",   "\\n"),
    ASCII(0x0B, "VT",   "^K",   "\\v"),
    ASCII(0x0C, "FF",   "^L",   "\\f"),
    ASCII(0x0D, "CR",   "^M",   "\\r"),
    ASCII(0x0E, "SO",   "^N",   ""),
    ASCII(0x0F, "SI",   "^O",   ""),
    ASCII(0x10, "DLE",  "^P",   ""),
    ASCII(0x11, "DC1",  "^Q",   ""),
    ASCII(0x12, "DC2",  "^R",   ""),
    ASCII(0x13, "DC3",  "^S",   ""),
    ASCII(0x14, "DC4",  "^T",   ""),
    ASCII(0x15, "NAK",  "^U",   ""),
    ASCII(0x16, "SYN",  "^V",   ""),
    ASCII(0x17, "ETB",  "^W",   ""),
    ASCII(0x18, "CAN",  "^X",   ""),
    ASCII(0x19, "EM",   "^Y",   ""),
    ASCII(0x1A, "SUB",  "^Z",   ""),
    ASCII(0x1B, "ESC",  "^[",   "\\e"),
    ASCII(0x1C, "FS",   "^\\",  ""),
    ASCII(0x1D, "GS"    "^]",   ""),
    ASCII(0x1E, "RS",   "^^",   ""),
    ASCII(0x1F, "US",   "^_",   ""),
    ASCII(0x7F, "DEL",  "^?",   ""),
    /* Printable Characters */
    ASCII(0x20, "Space",    "", ""),
    ASCII(0x21, "!",        "", ""),
    ASCII(0x22, "\"",       "", ""),
    ASCII(0x23, "#",        "", ""),

};









#endif /* __ASCII_H__ */
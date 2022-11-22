#pragma once

// ALL NOT NULL -- a variadic null-pointer checking Macro.
// http://co-hoppe.net/post/a_c_macro/

#include <stddef.h>

#define ann_expand1(p1) NULL == p1
#define ann_expand2(p1, p2) ann_expand1(p1) || ann_expand1(p2)
#define ann_expand3(p1, p2, p3) ann_expand2(p1, p2) || ann_expand1(p3)
#define ann_expand4(p1, p2, p3, p4) ann_expand3(p1, p2, p3) || ann_expand1(p4)
#define ann_expand5(p1, p2, p3, p4, p5) \
  ann_expand4(p1, p2, p3, p4) || ann_expand1(p5)
#define ann_expand6(p1, p2, p3, p4, p5, p6) \
  ann_expand5(p1, p2, p3, p4, p5) || ann_expand1(p6)
#define ann_expand7(p1, p2, p3, p4, p5, p6, p7) \
  ann_expand6(p1, p2, p3, p4, p5, p6) || ann_expand1(p7)
#define ann_expand8(p1, p2, p3, p4, p5, p6, p7, p8) \
  ann_expand7(p1, p2, p3, p4, p5, p6, p7) || ann_expand1(p8)
#define ann_expand9(p1, p2, p3, p4, p5, p6, p7, p8, p9) \
  ann_expand8(p1, p2, p3, p4, p5, p6, p7, p8) || ann_expand1(p9)
#define ann_expand10(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10) \
  ann_expand9(p1, p2, p3, p4, p5, p6, p7, p8, p9) || ann_expand1(p10)
#define ann_expand11(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11) \
  ann_expand10(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10) || ann_expand1(p11)
#define ann_expand12(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12) \
  ann_expand11(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11) || ann_expand1(p12)
#define ann_expand13(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13) \
  ann_expand12(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12) ||         \
      ann_expand1(p13)
#define ann_expand14(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, \
                     p14)                                                    \
  ann_expand13(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13) ||    \
      ann_expand1(p14)
#define ann_expand15(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13,   \
                     p14, p15)                                                 \
  ann_expand14(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14) || \
      ann_expand1(p15)
#define ann_expand16(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, \
                     p14, p15, p16)                                          \
  ann_expand15(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14,  \
               p15) ||                                                       \
      ann_expand1(p16)
#define ann_expand17(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, \
                     p14, p15, p16, p17)                                     \
  ann_expand16(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14,  \
               p15, p16) ||                                                  \
      ann_expand1(p17)
#define ann_expand18(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, \
                     p14, p15, p16, p17, p18)                                \
  ann_expand17(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14,  \
               p15, p16, p17) ||                                             \
      ann_expand1(p18)
#define ann_expand19(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, \
                     p14, p15, p16, p17, p18, p19)                           \
  ann_expand18(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14,  \
               p15, p16, p17, p18) ||                                        \
      ann_expand1(p19)
#define ann_expand20(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, \
                     p14, p15, p16, p17, p18, p19, p20)                      \
  ann_expand19(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14,  \
               p15, p16, p17, p18, p19) ||                                   \
      ann_expand1(p20)
#define ann_expand21(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, \
                     p14, p15, p16, p17, p18, p19, p20, p21)                 \
  ann_expand20(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14,  \
               p15, p16, p17, p18, p19, p20) ||                              \
      ann_expand1(p21)
#define ann_expand22(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, \
                     p14, p15, p16, p17, p18, p19, p20, p21, p22)            \
  ann_expand21(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14,  \
               p15, p16, p17, p18, p19, p20, p21) ||                         \
      ann_expand1(p22)
#define ann_expand23(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, \
                     p14, p15, p16, p17, p18, p19, p20, p21, p22, p23)       \
  ann_expand22(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14,  \
               p15, p16, p17, p18, p19, p20, p21, p22) ||                    \
      ann_expand1(p23)
#define ann_expand24(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, \
                     p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24)  \
  ann_expand23(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14,  \
               p15, p16, p17, p18, p19, p20, p21, p22, p23) ||               \
      ann_expand1(p24)
#define ann_expand25(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, \
                     p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24,  \
                     p25)                                                    \
  ann_expand24(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14,  \
               p15, p16, p17, p18, p19, p20, p21, p22, p23, p24) ||          \
      ann_expand1(p25)
#define ann_expand26(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, \
                     p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24,  \
                     p25, p26)                                               \
  ann_expand25(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14,  \
               p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25) ||     \
      ann_expand1(p26)
#define ann_expand27(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13,  \
                     p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24,   \
                     p25, p26, p27)                                           \
  ann_expand26(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14,   \
               p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26) || \
      ann_expand1(p27)
#define ann_expand28(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, \
                     p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24,  \
                     p25, p26, p27, p28)                                     \
  ann_expand27(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14,  \
               p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26,   \
               p27) ||                                                       \
      ann_expand1(p28)
#define ann_expand29(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, \
                     p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24,  \
                     p25, p26, p27, p28, p29)                                \
  ann_expand28(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14,  \
               p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26,   \
               p27, p28) ||                                                  \
      ann_expand1(p29)
#define ann_expand30(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, \
                     p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24,  \
                     p25, p26, p27, p28, p29, p30)                           \
  ann_expand29(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14,  \
               p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26,   \
               p27, p28, p29) ||                                             \
      ann_expand1(p30)
#define ann_expand31(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, \
                     p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24,  \
                     p25, p26, p27, p28, p29, p30, p31)                      \
  ann_expand30(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14,  \
               p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26,   \
               p27, p28, p29, p30) ||                                        \
      ann_expand1(p31)
#define ann_expand32(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, \
                     p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24,  \
                     p25, p26, p27, p28, p29, p30, p31, p32)                 \
  ann_expand31(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14,  \
               p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26,   \
               p27, p28, p29, p30, p31) ||                                   \
      ann_expand1(p32)
#define ann_expand33(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, \
                     p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24,  \
                     p25, p26, p27, p28, p29, p30, p31, p32, p33)            \
  ann_expand32(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14,  \
               p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26,   \
               p27, p28, p29, p30, p31, p32) ||                              \
      ann_expand1(p33)
#define ann_expand34(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, \
                     p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24,  \
                     p25, p26, p27, p28, p29, p30, p31, p32, p33, p34)       \
  ann_expand33(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14,  \
               p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26,   \
               p27, p28, p29, p30, p31, p32, p33) ||                         \
      ann_expand1(p34)
#define ann_expand35(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, \
                     p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24,  \
                     p25, p26, p27, p28, p29, p30, p31, p32, p33, p34, p35)  \
  ann_expand34(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14,  \
               p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26,   \
               p27, p28, p29, p30, p31, p32, p33, p34) ||                    \
      ann_expand1(p35)
#define ann_expand36(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, \
                     p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24,  \
                     p25, p26, p27, p28, p29, p30, p31, p32, p33, p34, p35,  \
                     p36)                                                    \
  ann_expand35(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14,  \
               p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26,   \
               p27, p28, p29, p30, p31, p32, p33, p34, p35) ||               \
      ann_expand1(p36)
#define ann_expand37(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, \
                     p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24,  \
                     p25, p26, p27, p28, p29, p30, p31, p32, p33, p34, p35,  \
                     p36, p37)                                               \
  ann_expand36(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14,  \
               p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26,   \
               p27, p28, p29, p30, p31, p32, p33, p34, p35, p36) ||          \
      ann_expand1(p37)
#define ann_expand38(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, \
                     p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24,  \
                     p25, p26, p27, p28, p29, p30, p31, p32, p33, p34, p35,  \
                     p36, p37, p38)                                          \
  ann_expand37(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14,  \
               p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26,   \
               p27, p28, p29, p30, p31, p32, p33, p34, p35, p36, p37) ||     \
      ann_expand1(p38)
#define ann_expand39(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13,  \
                     p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24,   \
                     p25, p26, p27, p28, p29, p30, p31, p32, p33, p34, p35,   \
                     p36, p37, p38, p39)                                      \
  ann_expand38(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14,   \
               p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26,    \
               p27, p28, p29, p30, p31, p32, p33, p34, p35, p36, p37, p38) || \
      ann_expand1(p39)
#define ann_expand40(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, \
                     p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24,  \
                     p25, p26, p27, p28, p29, p30, p31, p32, p33, p34, p35,  \
                     p36, p37, p38, p39, p40)                                \
  ann_expand39(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14,  \
               p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26,   \
               p27, p28, p29, p30, p31, p32, p33, p34, p35, p36, p37, p38,   \
               p39) ||                                                       \
      ann_expand1(p40)
#define ann_expand41(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, \
                     p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24,  \
                     p25, p26, p27, p28, p29, p30, p31, p32, p33, p34, p35,  \
                     p36, p37, p38, p39, p40, p41)                           \
  ann_expand40(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14,  \
               p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26,   \
               p27, p28, p29, p30, p31, p32, p33, p34, p35, p36, p37, p38,   \
               p39, p40) ||                                                  \
      ann_expand1(p41)
#define ann_expand42(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, \
                     p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24,  \
                     p25, p26, p27, p28, p29, p30, p31, p32, p33, p34, p35,  \
                     p36, p37, p38, p39, p40, p41, p42)                      \
  ann_expand41(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14,  \
               p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26,   \
               p27, p28, p29, p30, p31, p32, p33, p34, p35, p36, p37, p38,   \
               p39, p40, p41) ||                                             \
      ann_expand1(p42)
#define ann_expand43(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, \
                     p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24,  \
                     p25, p26, p27, p28, p29, p30, p31, p32, p33, p34, p35,  \
                     p36, p37, p38, p39, p40, p41, p42, p43)                 \
  ann_expand42(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14,  \
               p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26,   \
               p27, p28, p29, p30, p31, p32, p33, p34, p35, p36, p37, p38,   \
               p39, p40, p41, p42) ||                                        \
      ann_expand1(p43)
#define ann_expand44(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, \
                     p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24,  \
                     p25, p26, p27, p28, p29, p30, p31, p32, p33, p34, p35,  \
                     p36, p37, p38, p39, p40, p41, p42, p43, p44)            \
  ann_expand43(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14,  \
               p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26,   \
               p27, p28, p29, p30, p31, p32, p33, p34, p35, p36, p37, p38,   \
               p39, p40, p41, p42, p43) ||                                   \
      ann_expand1(p44)
#define ann_expand45(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, \
                     p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24,  \
                     p25, p26, p27, p28, p29, p30, p31, p32, p33, p34, p35,  \
                     p36, p37, p38, p39, p40, p41, p42, p43, p44, p45)       \
  ann_expand44(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14,  \
               p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26,   \
               p27, p28, p29, p30, p31, p32, p33, p34, p35, p36, p37, p38,   \
               p39, p40, p41, p42, p43, p44) ||                              \
      ann_expand1(p45)
#define ann_expand46(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, \
                     p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24,  \
                     p25, p26, p27, p28, p29, p30, p31, p32, p33, p34, p35,  \
                     p36, p37, p38, p39, p40, p41, p42, p43, p44, p45, p46)  \
  ann_expand45(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14,  \
               p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26,   \
               p27, p28, p29, p30, p31, p32, p33, p34, p35, p36, p37, p38,   \
               p39, p40, p41, p42, p43, p44, p45) ||                         \
      ann_expand1(p46)
#define ann_expand47(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, \
                     p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24,  \
                     p25, p26, p27, p28, p29, p30, p31, p32, p33, p34, p35,  \
                     p36, p37, p38, p39, p40, p41, p42, p43, p44, p45, p46,  \
                     p47)                                                    \
  ann_expand46(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14,  \
               p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26,   \
               p27, p28, p29, p30, p31, p32, p33, p34, p35, p36, p37, p38,   \
               p39, p40, p41, p42, p43, p44, p45, p46) ||                    \
      ann_expand1(p47)
#define ann_expand48(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, \
                     p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24,  \
                     p25, p26, p27, p28, p29, p30, p31, p32, p33, p34, p35,  \
                     p36, p37, p38, p39, p40, p41, p42, p43, p44, p45, p46,  \
                     p47, p48)                                               \
  ann_expand47(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14,  \
               p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26,   \
               p27, p28, p29, p30, p31, p32, p33, p34, p35, p36, p37, p38,   \
               p39, p40, p41, p42, p43, p44, p45, p46, p47) ||               \
      ann_expand1(p48)
#define ann_expand49(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, \
                     p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24,  \
                     p25, p26, p27, p28, p29, p30, p31, p32, p33, p34, p35,  \
                     p36, p37, p38, p39, p40, p41, p42, p43, p44, p45, p46,  \
                     p47, p48, p49)                                          \
  ann_expand48(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14,  \
               p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26,   \
               p27, p28, p29, p30, p31, p32, p33, p34, p35, p36, p37, p38,   \
               p39, p40, p41, p42, p43, p44, p45, p46, p47, p48) ||          \
      ann_expand1(p49)
#define ann_expand50(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, \
                     p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24,  \
                     p25, p26, p27, p28, p29, p30, p31, p32, p33, p34, p35,  \
                     p36, p37, p38, p39, p40, p41, p42, p43, p44, p45, p46,  \
                     p47, p48, p49, p50)                                     \
  ann_expand49(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14,  \
               p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26,   \
               p27, p28, p29, p30, p31, p32, p33, p34, p35, p36, p37, p38,   \
               p39, p40, p41, p42, p43, p44, p45, p46, p47, p48, p49) ||     \
      ann_expand1(p50)
#define ann_expand51(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13,  \
                     p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24,   \
                     p25, p26, p27, p28, p29, p30, p31, p32, p33, p34, p35,   \
                     p36, p37, p38, p39, p40, p41, p42, p43, p44, p45, p46,   \
                     p47, p48, p49, p50, p51)                                 \
  ann_expand50(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14,   \
               p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26,    \
               p27, p28, p29, p30, p31, p32, p33, p34, p35, p36, p37, p38,    \
               p39, p40, p41, p42, p43, p44, p45, p46, p47, p48, p49, p50) || \
      ann_expand1(p51)
#define ann_expand52(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, \
                     p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24,  \
                     p25, p26, p27, p28, p29, p30, p31, p32, p33, p34, p35,  \
                     p36, p37, p38, p39, p40, p41, p42, p43, p44, p45, p46,  \
                     p47, p48, p49, p50, p51, p52)                           \
  ann_expand51(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14,  \
               p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26,   \
               p27, p28, p29, p30, p31, p32, p33, p34, p35, p36, p37, p38,   \
               p39, p40, p41, p42, p43, p44, p45, p46, p47, p48, p49, p50,   \
               p51) ||                                                       \
      ann_expand1(p52)
#define ann_expand53(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, \
                     p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24,  \
                     p25, p26, p27, p28, p29, p30, p31, p32, p33, p34, p35,  \
                     p36, p37, p38, p39, p40, p41, p42, p43, p44, p45, p46,  \
                     p47, p48, p49, p50, p51, p52, p53)                      \
  ann_expand52(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14,  \
               p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26,   \
               p27, p28, p29, p30, p31, p32, p33, p34, p35, p36, p37, p38,   \
               p39, p40, p41, p42, p43, p44, p45, p46, p47, p48, p49, p50,   \
               p51, p52) ||                                                  \
      ann_expand1(p53)
#define ann_expand54(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, \
                     p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24,  \
                     p25, p26, p27, p28, p29, p30, p31, p32, p33, p34, p35,  \
                     p36, p37, p38, p39, p40, p41, p42, p43, p44, p45, p46,  \
                     p47, p48, p49, p50, p51, p52, p53, p54)                 \
  ann_expand53(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14,  \
               p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26,   \
               p27, p28, p29, p30, p31, p32, p33, p34, p35, p36, p37, p38,   \
               p39, p40, p41, p42, p43, p44, p45, p46, p47, p48, p49, p50,   \
               p51, p52, p53) ||                                             \
      ann_expand1(p54)
#define ann_expand55(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, \
                     p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24,  \
                     p25, p26, p27, p28, p29, p30, p31, p32, p33, p34, p35,  \
                     p36, p37, p38, p39, p40, p41, p42, p43, p44, p45, p46,  \
                     p47, p48, p49, p50, p51, p52, p53, p54, p55)            \
  ann_expand54(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14,  \
               p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26,   \
               p27, p28, p29, p30, p31, p32, p33, p34, p35, p36, p37, p38,   \
               p39, p40, p41, p42, p43, p44, p45, p46, p47, p48, p49, p50,   \
               p51, p52, p53, p54) ||                                        \
      ann_expand1(p55)
#define ann_expand56(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, \
                     p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24,  \
                     p25, p26, p27, p28, p29, p30, p31, p32, p33, p34, p35,  \
                     p36, p37, p38, p39, p40, p41, p42, p43, p44, p45, p46,  \
                     p47, p48, p49, p50, p51, p52, p53, p54, p55, p56)       \
  ann_expand55(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14,  \
               p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26,   \
               p27, p28, p29, p30, p31, p32, p33, p34, p35, p36, p37, p38,   \
               p39, p40, p41, p42, p43, p44, p45, p46, p47, p48, p49, p50,   \
               p51, p52, p53, p54, p55) ||                                   \
      ann_expand1(p56)
#define ann_expand57(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, \
                     p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24,  \
                     p25, p26, p27, p28, p29, p30, p31, p32, p33, p34, p35,  \
                     p36, p37, p38, p39, p40, p41, p42, p43, p44, p45, p46,  \
                     p47, p48, p49, p50, p51, p52, p53, p54, p55, p56, p57)  \
  ann_expand56(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14,  \
               p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26,   \
               p27, p28, p29, p30, p31, p32, p33, p34, p35, p36, p37, p38,   \
               p39, p40, p41, p42, p43, p44, p45, p46, p47, p48, p49, p50,   \
               p51, p52, p53, p54, p55, p56) ||                              \
      ann_expand1(p57)
#define ann_expand58(                                                          \
    p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16,     \
    p17, p18, p19, p20, p21, p22, p23, p24, p25, p26, p27, p28, p29, p30, p31, \
    p32, p33, p34, p35, p36, p37, p38, p39, p40, p41, p42, p43, p44, p45, p46, \
    p47, p48, p49, p50, p51, p52, p53, p54, p55, p56, p57, p58)                \
  ann_expand57(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14,    \
               p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26,     \
               p27, p28, p29, p30, p31, p32, p33, p34, p35, p36, p37, p38,     \
               p39, p40, p41, p42, p43, p44, p45, p46, p47, p48, p49, p50,     \
               p51, p52, p53, p54, p55, p56, p57) ||                           \
      ann_expand1(p58)
#define ann_expand59(                                                          \
    p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16,     \
    p17, p18, p19, p20, p21, p22, p23, p24, p25, p26, p27, p28, p29, p30, p31, \
    p32, p33, p34, p35, p36, p37, p38, p39, p40, p41, p42, p43, p44, p45, p46, \
    p47, p48, p49, p50, p51, p52, p53, p54, p55, p56, p57, p58, p59)           \
  ann_expand58(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14,    \
               p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26,     \
               p27, p28, p29, p30, p31, p32, p33, p34, p35, p36, p37, p38,     \
               p39, p40, p41, p42, p43, p44, p45, p46, p47, p48, p49, p50,     \
               p51, p52, p53, p54, p55, p56, p57, p58) ||                      \
      ann_expand1(p59)
#define ann_expand60(                                                          \
    p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16,     \
    p17, p18, p19, p20, p21, p22, p23, p24, p25, p26, p27, p28, p29, p30, p31, \
    p32, p33, p34, p35, p36, p37, p38, p39, p40, p41, p42, p43, p44, p45, p46, \
    p47, p48, p49, p50, p51, p52, p53, p54, p55, p56, p57, p58, p59, p60)      \
  ann_expand59(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14,    \
               p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26,     \
               p27, p28, p29, p30, p31, p32, p33, p34, p35, p36, p37, p38,     \
               p39, p40, p41, p42, p43, p44, p45, p46, p47, p48, p49, p50,     \
               p51, p52, p53, p54, p55, p56, p57, p58, p59) ||                 \
      ann_expand1(p60)
#define ann_expand61(                                                          \
    p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16,     \
    p17, p18, p19, p20, p21, p22, p23, p24, p25, p26, p27, p28, p29, p30, p31, \
    p32, p33, p34, p35, p36, p37, p38, p39, p40, p41, p42, p43, p44, p45, p46, \
    p47, p48, p49, p50, p51, p52, p53, p54, p55, p56, p57, p58, p59, p60, p61) \
  ann_expand60(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14,    \
               p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26,     \
               p27, p28, p29, p30, p31, p32, p33, p34, p35, p36, p37, p38,     \
               p39, p40, p41, p42, p43, p44, p45, p46, p47, p48, p49, p50,     \
               p51, p52, p53, p54, p55, p56, p57, p58, p59, p60) ||            \
      ann_expand1(p61)
#define ann_expand62(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, \
                     p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24,  \
                     p25, p26, p27, p28, p29, p30, p31, p32, p33, p34, p35,  \
                     p36, p37, p38, p39, p40, p41, p42, p43, p44, p45, p46,  \
                     p47, p48, p49, p50, p51, p52, p53, p54, p55, p56, p57,  \
                     p58, p59, p60, p61, p62)                                \
  ann_expand61(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14,  \
               p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26,   \
               p27, p28, p29, p30, p31, p32, p33, p34, p35, p36, p37, p38,   \
               p39, p40, p41, p42, p43, p44, p45, p46, p47, p48, p49, p50,   \
               p51, p52, p53, p54, p55, p56, p57, p58, p59, p60, p61) ||     \
      ann_expand1(p62)

// thanks to comp.std.c for this set of length determining macros
#define PP_NARG(...) PP_NARG_(__VA_ARGS__, PP_RSEQ_N())
#define PP_NARG_(...) PP_ARG_N(__VA_ARGS__)
#define PP_ARG_N(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, \
                 _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26,  \
                 _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38,  \
                 _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50,  \
                 _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62,  \
                 _63, N, ...)                                                 \
  N
#define PP_RSEQ_N()                                                           \
  63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, \
      44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, \
      26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9,  \
      8, 7, 6, 5, 4, 3, 2, 1, 0
/// end thanks

#define all_not_null(orelse, ...)                                      \
  if (ann_dispatch_1(ann_expand, PP_NARG(__VA_ARGS__))(__VA_ARGS__)) { \
    orelse                                                             \
  }

#define ann_dispatch_1(func, nargs) ann_dispatch_2(func, nargs)

#define ann_dispatch_2(func, nargs) func##nargs

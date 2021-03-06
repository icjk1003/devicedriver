#define GPIO_BASE	0x3F200000
#define GPIO_SIZE	180

#define GPIO_IN(g)	(*(gpio + (g / 10)) &= ~(7 << ((g % 10) * 3)))
#define GPIO_OUT(g)	(*(gpio + (g / 10)) |= (1 << ((g % 10) * 3)))
#define GPIO_SET(g)	(*(gpio + 7) = 1 << g)
#define GPIO_CLR(g)	(*(gpio + 10) = 1 << g)
#define GPIO_GET(g)	(*(gpio + 13) & (1 << g))

#define GPIO_LED	18

volatile unsigned *gpio;

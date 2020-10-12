#ifndef __UTILS_H_
#define __UTILS_H_

#if __BYTE_ORDER == __LITTLE_ENDIAN
# define __bpf_ntohs(x)		__builtin_bswap16(x)
# define __bpf_htons(x)		__builtin_bswap16(x)
# define __bpf_ntohl(x)		__builtin_bswap32(x)
# define __bpf_htonl(x)		__builtin_bswap32(x)
#elif __BYTE_ORDER == __BIG_ENDIAN
# define __bpf_ntohs(x)		(x)
# define __bpf_htons(x)		(x)
# define __bpf_ntohl(x)		(x)
# define __bpf_htonl(x)		(x)
#else
# error "Fix your __BYTE_ORDER?!"
#endif

#define bpf_htons(x)				\
	(__builtin_constant_p(x) ?		\
	 __constant_htons(x) : __bpf_htons(x))
#define bpf_ntohs(x)				\
	(__builtin_constant_p(x) ?		\
	 __constant_ntohs(x) : __bpf_ntohs(x))

#define bpf_htonl(x)				\
	(__builtin_constant_p(x) ?		\
	 __constant_htonl(x) : __bpf_htonl(x))
#define bpf_ntohl(x)				\
	(__builtin_constant_p(x) ?		\
	 __constant_ntohl(x) : __bpf_ntohl(x))
#endif

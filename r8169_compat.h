// r8169.c compatibility layer for building on kernel 3.2.x ... 3.18.x
// Written (mostly copypasted) by [anp/hsw] and distributed according to GPLv3 License
#ifndef _R8169_COMPAT_H
#define _R8169_COMPAT_H

#include <linux/version.h>

#if (LINUX_VERSION_CODE < KERNEL_VERSION(3, 4, 0))

// convert driver hook to 3.2 structure
#ifndef module_pci_driver

#define module_pci_driver(driver)				\
static int __init rtl8169_init_module(void)			\
{								\
        return pci_register_driver(&driver);			\
}								\
static void __exit rtl8169_cleanup_module(void)			\
{								\
        pci_unregister_driver(&driver);				\
}								\
module_init(rtl8169_init_module);				\
module_exit(rtl8169_cleanup_module);				\

#endif
// end driver hook

typedef u64 netdev_features_t;
enum {
        NETIF_F_SG_BIT,                 /* Scatter/gather IO. */
        NETIF_F_IP_CSUM_BIT,            /* Can checksum TCP/UDP over IPv4. */
        __UNUSED_NETIF_F_1,
        NETIF_F_HW_CSUM_BIT,            /* Can checksum all the packets. */
        NETIF_F_IPV6_CSUM_BIT,          /* Can checksum TCP/UDP over IPV6 */
        NETIF_F_HIGHDMA_BIT,            /* Can DMA to high memory. */
        NETIF_F_FRAGLIST_BIT,           /* Scatter/gather IO. */
        NETIF_F_HW_VLAN_CTAG_TX_BIT,    /* Transmit VLAN CTAG HW acceleration */
        NETIF_F_HW_VLAN_CTAG_RX_BIT,    /* Receive VLAN CTAG HW acceleration */
        NETIF_F_HW_VLAN_CTAG_FILTER_BIT,/* Receive filtering on VLAN CTAGs */
        NETIF_F_VLAN_CHALLENGED_BIT,    /* Device cannot handle VLAN packets */
        NETIF_F_GSO_BIT,                /* Enable software GSO. */
        NETIF_F_LLTX_BIT,               /* LockLess TX - deprecated. Please */
                                        /* do not use LLTX in new drivers */
        NETIF_F_NETNS_LOCAL_BIT,        /* Does not change network namespaces */
        NETIF_F_GRO_BIT,                /* Generic receive offload */
        NETIF_F_LRO_BIT,                /* large receive offload */

        /*NETIF_F_GSO_SHIFT,*/          /* keep the order of SKB_GSO_* bits */
        NETIF_F_TSO_BIT                 /* ... TCPv4 segmentation */
                = NETIF_F_GSO_SHIFT,
        NETIF_F_UFO_BIT,                /* ... UDPv4 fragmentation */
        NETIF_F_GSO_ROBUST_BIT,         /* ... ->SKB_GSO_DODGY */
        NETIF_F_TSO_ECN_BIT,            /* ... TCP ECN support */
        NETIF_F_TSO6_BIT,               /* ... TCPv6 segmentation */
        NETIF_F_FSO_BIT,                /* ... FCoE segmentation */
        NETIF_F_GSO_GRE_BIT,            /* ... GRE with TSO */
        NETIF_F_GSO_UDP_TUNNEL_BIT,     /* ... UDP TUNNEL with TSO */
        /**/NETIF_F_GSO_LAST =          /* last bit, see GSO_MASK */
                NETIF_F_GSO_UDP_TUNNEL_BIT,

        NETIF_F_FCOE_CRC_BIT,           /* FCoE CRC32 */
        NETIF_F_SCTP_CSUM_BIT,          /* SCTP checksum offload */
        NETIF_F_FCOE_MTU_BIT,           /* Supports max FCoE MTU, 2158 bytes*/
        NETIF_F_NTUPLE_BIT,             /* N-tuple filters supported */
        NETIF_F_RXHASH_BIT,             /* Receive hashing offload */
        NETIF_F_RXCSUM_BIT,             /* Receive checksumming offload */
        NETIF_F_NOCACHE_COPY_BIT,       /* Use no-cache copyfromuser */
        NETIF_F_LOOPBACK_BIT,           /* Enable loopback */
        NETIF_F_RXFCS_BIT,              /* Append FCS to skb pkt data */
        NETIF_F_RXALL_BIT,              /* Receive errored frames too */
        NETIF_F_HW_VLAN_STAG_TX_BIT,    /* Transmit VLAN STAG HW acceleration */
        NETIF_F_HW_VLAN_STAG_RX_BIT,    /* Receive VLAN STAG HW acceleration */
        NETIF_F_HW_VLAN_STAG_FILTER_BIT,/* Receive filtering on VLAN STAGs */

        /*
         * Add your fresh new feature above and remember to update
         * netdev_features_strings[] in net/core/ethtool.c and maybe
         * some feature mask #defines below. Please also describe it
         * in Documentation/networking/netdev-features.txt.
         */

        /**/NETDEV_FEATURE_COUNT
};

/* copy'n'paste compression ;) */
#define __NETIF_F_BIT(bit)      ((netdev_features_t)1 << (bit))
#define __NETIF_F(name)         __NETIF_F_BIT(NETIF_F_##name##_BIT)

#define NETIF_F_HW_VLAN_CTAG_FILTER __NETIF_F(HW_VLAN_CTAG_FILTER)
#define NETIF_F_HW_VLAN_CTAG_RX __NETIF_F(HW_VLAN_CTAG_RX)
#define NETIF_F_HW_VLAN_CTAG_TX __NETIF_F(HW_VLAN_CTAG_TX)
#define NETIF_F_HW_VLAN_STAG_FILTER __NETIF_F(HW_VLAN_STAG_FILTER)
#define NETIF_F_HW_VLAN_STAG_RX __NETIF_F(HW_VLAN_STAG_RX)
#define NETIF_F_HW_VLAN_STAG_TX __NETIF_F(HW_VLAN_STAG_TX)

#define NETIF_F_RXFCS           __NETIF_F(RXFCS)
#define NETIF_F_RXALL           __NETIF_F(RXALL)

static inline void eth_hw_addr_random(struct net_device *dev)
{
    dev->addr_assign_type |= NET_ADDR_RANDOM;
    random_ether_addr(dev->dev_addr);
}

#endif //(LINUX_VERSION_CODE < KERNEL_VERSION(3, 4, 0))

#if (LINUX_VERSION_CODE < KERNEL_VERSION(3, 6, 0))
// set get_ts_info to any unused hook in driver
#define get_ts_info		self_test
#define ethtool_op_get_ts_info	NULL
#endif //(LINUX_VERSION_CODE < KERNEL_VERSION(3, 6, 0))

#if (LINUX_VERSION_CODE < KERNEL_VERSION(3, 8, 0))
static int pcie_capability_clear_and_set_word(struct pci_dev *pdev, int pos,
                                       u16 clear, u16 set)
{
        int cap = pci_pcie_cap(pdev);

        if (cap) {
                u16 ctl;

                pci_read_config_word(pdev, cap + pos, &ctl);
                ctl = (ctl & ~clear) | set;
                pci_write_config_word(pdev, cap + pos, ctl);
        }
        return 0;
}
static inline int pcie_capability_set_word(struct pci_dev *dev, int pos,
                                           u16 set)
{
        return pcie_capability_clear_and_set_word(dev, pos, 0, set);
}
static inline int pcie_capability_clear_word(struct pci_dev *dev, int pos,
                                             u16 clear)
{
        return pcie_capability_clear_and_set_word(dev, pos, clear, 0);
}
static inline __sum16 tcp_v6_check(int len,
		   const struct in6_addr *saddr,
		   const struct in6_addr *daddr,
		   __wsum base)
{
    return csum_ipv6_magic(saddr, daddr, len, IPPROTO_TCP, base);
}

#define __vlan_hwaccel_put_tag(skb, mac, opts) __vlan_hwaccel_put_tag(skb, opts) 

#endif //(LINUX_VERSION_CODE < KERNEL_VERSION(3, 8, 0))

#if (LINUX_VERSION_CODE < KERNEL_VERSION(3, 14, 0))

#if BITS_PER_LONG == 32 && defined(CONFIG_SMP)
# define u64_stats_init(syncp)  seqcount_init(syncp.seq)
#else
# define u64_stats_init(syncp)  do { } while (0)
#endif
#define u64_stats_fetch_begin_irq u64_stats_fetch_begin_bh
#define u64_stats_fetch_retry_irq u64_stats_fetch_retry_bh

#define dev_consume_skb_any dev_kfree_skb_any

#endif //(LINUX_VERSION_CODE < KERNEL_VERSION(3, 14, 0))

#endif //_R8169_COMPAT_H

#ifndef RADIOTAP_FLAGS_H
#define RADIOTAP_FLAGS_H

/* (C) 2014 - 2017 rofl0r
   released under the public domain.
*/

#include <stdint.h>

/* prevent redefining the same types when the official radiotap
   header is in use too */
#ifndef IEEE80211RADIOTAP_H

struct ieee80211_radiotap_header {
	uint8_t it_version;
	uint8_t it_pad;
	uint16_t it_len;
	uint32_t it_present;
};

enum ieee80211_radiotap_type {
	IEEE80211_RADIOTAP_TSFT = 0,
	IEEE80211_RADIOTAP_FLAGS = 1,
	IEEE80211_RADIOTAP_RATE = 2,
	IEEE80211_RADIOTAP_CHANNEL = 3,
	IEEE80211_RADIOTAP_FHSS = 4,
	IEEE80211_RADIOTAP_DBM_ANTSIGNAL = 5,
	IEEE80211_RADIOTAP_DBM_ANTNOISE = 6,
	IEEE80211_RADIOTAP_LOCK_QUALITY = 7,
	IEEE80211_RADIOTAP_TX_ATTENUATION = 8,
	IEEE80211_RADIOTAP_DB_TX_ATTENUATION = 9,
	IEEE80211_RADIOTAP_DBM_TX_POWER = 10,
	IEEE80211_RADIOTAP_ANTENNA = 11,
	IEEE80211_RADIOTAP_DB_ANTSIGNAL = 12,
	IEEE80211_RADIOTAP_DB_ANTNOISE = 13,
	IEEE80211_RADIOTAP_RX_FLAGS = 14,
	IEEE80211_RADIOTAP_TX_FLAGS = 15,
	IEEE80211_RADIOTAP_RTS_RETRIES = 16,
	IEEE80211_RADIOTAP_DATA_RETRIES = 17,
	IEEE80211_RADIOTAP_XCHANNEL = 18,
	IEEE80211_RADIOTAP_MCS = 19,
	IEEE80211_RADIOTAP_AMPDU_STATUS = 20,
	IEEE80211_RADIOTAP_VHT = 21,
	IEEE80211_RADIOTAP_TIMESTAMP = 22,
	IEEE80211_RADIOTAP_RADIOTAP_NAMESPACE = 29,
	IEEE80211_RADIOTAP_VENDOR_NAMESPACE = 30,
	IEEE80211_RADIOTAP_EXT = 31
};

#endif

static const unsigned char ieee80211_radiotap_type_size[] = {
	[IEEE80211_RADIOTAP_TSFT] = 8,
	[IEEE80211_RADIOTAP_FLAGS] = 1,
	[IEEE80211_RADIOTAP_RATE] = 1,
	[IEEE80211_RADIOTAP_CHANNEL] = 2*2,
	[IEEE80211_RADIOTAP_FHSS] = 2,
	[IEEE80211_RADIOTAP_DBM_ANTSIGNAL] = 1,
	[IEEE80211_RADIOTAP_DBM_ANTNOISE] = 1,
	[IEEE80211_RADIOTAP_LOCK_QUALITY] = 2,
	[IEEE80211_RADIOTAP_TX_ATTENUATION] = 2,
	[IEEE80211_RADIOTAP_DB_TX_ATTENUATION] = 2,
	[IEEE80211_RADIOTAP_DBM_TX_POWER] = 1,
	[IEEE80211_RADIOTAP_ANTENNA] = 1,
	[IEEE80211_RADIOTAP_DB_ANTSIGNAL] = 1,
	[IEEE80211_RADIOTAP_DB_ANTNOISE] = 1,
	[IEEE80211_RADIOTAP_RX_FLAGS] = 2,
	[IEEE80211_RADIOTAP_TX_FLAGS] = 2,
	[IEEE80211_RADIOTAP_RTS_RETRIES] = 1,
	[IEEE80211_RADIOTAP_DATA_RETRIES] = 1,
	[IEEE80211_RADIOTAP_MCS] = 1+1+1,
	[IEEE80211_RADIOTAP_AMPDU_STATUS] = 4+2+1+1,
	[IEEE80211_RADIOTAP_VHT] = 12,
	[IEEE80211_RADIOTAP_TIMESTAMP] = 12,
};

static const unsigned char ieee80211_radiotap_type_align[] = {
	[IEEE80211_RADIOTAP_TSFT] = 8,
	[IEEE80211_RADIOTAP_FLAGS] = 1,
	[IEEE80211_RADIOTAP_RATE] = 1,
	[IEEE80211_RADIOTAP_CHANNEL] = 2,
	[IEEE80211_RADIOTAP_FHSS] = 2,
	[IEEE80211_RADIOTAP_DBM_ANTSIGNAL] = 1,
	[IEEE80211_RADIOTAP_DBM_ANTNOISE] = 1,
	[IEEE80211_RADIOTAP_LOCK_QUALITY] = 2,
	[IEEE80211_RADIOTAP_TX_ATTENUATION] = 2,
	[IEEE80211_RADIOTAP_DB_TX_ATTENUATION] = 2,
	[IEEE80211_RADIOTAP_DBM_TX_POWER] = 1,
	[IEEE80211_RADIOTAP_ANTENNA] = 1,
	[IEEE80211_RADIOTAP_DB_ANTSIGNAL] = 1,
	[IEEE80211_RADIOTAP_DB_ANTNOISE] = 1,
	[IEEE80211_RADIOTAP_RX_FLAGS] = 2,
	[IEEE80211_RADIOTAP_TX_FLAGS] = 2,
	[IEEE80211_RADIOTAP_RTS_RETRIES] = 1,
	[IEEE80211_RADIOTAP_DATA_RETRIES] = 1,
	[IEEE80211_RADIOTAP_MCS] = 1,
	[IEEE80211_RADIOTAP_AMPDU_STATUS] = 4,
	[IEEE80211_RADIOTAP_VHT] = 2,
	[IEEE80211_RADIOTAP_TIMESTAMP] = 8,
};

/* get offset of the specified flag, starting from start_off */
static uint32_t rt_get_flag_offset(uint32_t pflags, uint32_t which, uint32_t start_off)
{
	unsigned i,c=start_off;
	for(i=0;i<which;i++) if(pflags & (1U << i)) {
		c+= c & (ieee80211_radiotap_type_align[i]-1);
		c+= ieee80211_radiotap_type_size[i];
	}
	return c;
}

#include <string.h>

#include "utils/endianness.h"

/* get present flags and offset of just after the radiotap header end.
   returns 1 on succes, 0 on bogus data */
static int rt_get_presentflags(const void *data, size_t len, uint32_t *pflags, uint32_t *offset)
{
	const struct ieee80211_radiotap_header* rh = data;
	*offset = sizeof(*rh);
	uint32_t fc = *pflags = end_le32toh(rh->it_present);
	while(fc & (1U << IEEE80211_RADIOTAP_EXT)) {
		if (*offset > len - 4) return 0;
		memcpy(&fc, data + *offset, 4);
		fc = end_le32toh(fc);
		*offset += 4;
	}
	return 1;
}

#endif

/**
 * libcalrom - temporale
 *
 * Private module encapsulating temporale logic
 */

#ifndef CALROM_TEMPORALE_H
#define CALROM_TEMPORALE_H

/**
 * Populates temporale with data for the specified year
 */
void temporale_init(CRTemporale *temporale, CRLiturgicalYear year);

/**
 * Populates season info for a specified date
 */
void temporale_season(CRSeasonInfo *season_info, const GDate *date, const CRTemporale *temporale);

#endif

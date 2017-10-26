/**
 * libcalrom - dates
 *
 * Private module computing dates of temporale feasts.
 */

#ifndef CALROM_DATES_H
#define CALROM_DATES_H

#include "calrom.h"

static const int WEEK = 7;

/**
 * Sets date to date of the first Advent Sunday
 */
void date_first_advent(GDate *date, const GDate *nativity);

void date_first_advent_in_year(GDate *date, CRLiturgicalYear year);

/**
 * Sets date to date of Nativity of the given liturgical year
 */
void date_nativity(GDate *date, CRLiturgicalYear year);

#endif

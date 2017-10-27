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
 * Sets date to the following Sunday
 */
void date_following_sunday(GDate *date);

/**
 * Sets date to date of the first Advent Sunday
 */
void date_first_advent(GDate *date, const GDate *nativity);

void date_first_advent_in_year(GDate *date, CRLiturgicalYear year);

/**
 * Sets date to date of Nativity of the given liturgical year
 */
void date_nativity(GDate *date, CRLiturgicalYear year);

void date_baptism_of_lord(GDate *date, CRLiturgicalYear year);

void date_ash_wednesday(GDate *date, const GDate *easter);

void date_easter(GDate *date, CRLiturgicalYear year);

void date_pentecost(GDate *date, const GDate *easter);

#endif

/**
 * libcalrom
 *
 * C library for calendar computations according to
 * the Roman Catholic liturgical calendar as instituted by
 * MP Mysterii Paschalis of Paul VI. (AAS 61 (1969), pp. 222-226).
 *
 * This header file declares the only public interface of the library.
 */

#ifndef CALROM_H
#define CALROM_H

#include <glib.h>

typedef enum {
  CR_SEASON_ADVENT,
  CR_SEASON_CHRISTMAS,
  CR_SEASON_LENT,
  CR_SEASON_EASTER,
  CR_SEASON_ORDINARY
} CRSeason;

typedef struct {
  CRSeason season;
  short week;
} CRSeasonInfo;

typedef GDateYear CRLiturgicalYear;

typedef struct {
  GDate first_advent_date;
  GDate nativity_date;
  GDate baptism_of_lord_date;
  GDate ash_wednesday_date;
  GDate easter_date;
  GDate pentecost_date;
} CRTemporale;

typedef struct {
} CRSanctorale;

typedef struct {
  CRLiturgicalYear year;
  GDate beginning_date;
  GDate end_date;
  CRTemporale temporale;
} CRCalendar;

typedef struct {
} CRCelebration;

typedef struct {
  CRSeasonInfo season_info;
} CRDay;

/**
 * Determines liturgical year.
 */
CRLiturgicalYear calrom_year(const GDate *date);

/**
 * Builds calendar for the specified liturgical year.
 */
void calrom_build_calendar(CRCalendar *calendar, CRLiturgicalYear year, const CRSanctorale *sanctorale);

/**
 * Populates day with liturgical calendar data for the given date.
 * Returns 1 on success or an error code (negative number).
 */
int calrom_day(CRDay *day, const GDate *date, const CRCalendar *calendar);

#endif

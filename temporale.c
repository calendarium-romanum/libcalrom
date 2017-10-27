#include "calrom.h"
#include "dates.h"
#include "temporale.h"

// date comparison shorthands
#define dt_lt(a, b) g_date_compare(a, b) < 0
#define dt_le(a, b) g_date_compare(a, b) <= 0

void temporale_init(CRTemporale *temporale, CRLiturgicalYear year)
{
  // slightly dirty use of pointer arithmetics
  g_date_clear(&(temporale->first_advent_date), sizeof(CRTemporale) / sizeof(GDate));

  date_nativity(&(temporale->nativity_date), year);
  date_first_advent(&(temporale->first_advent_date), &(temporale->nativity_date));
  date_baptism_of_lord(&(temporale->baptism_of_lord_date), year);
  date_easter(&(temporale->easter_date), year);
  date_ash_wednesday(&(temporale->ash_wednesday_date), &(temporale->easter_date));
  date_pentecost(&(temporale->pentecost_date), &(temporale->easter_date));
}

void temporale_season(CRSeasonInfo *season_info, const GDate *date, const CRTemporale *temporale)
{
  if (dt_lt(date, &(temporale->nativity_date))) {
    season_info->season = CR_SEASON_ADVENT;
  } else if (dt_le(date, &(temporale->baptism_of_lord_date))) {
    season_info->season = CR_SEASON_CHRISTMAS;
  } else if (dt_lt(date, &(temporale->ash_wednesday_date))) {
    season_info->season = CR_SEASON_ORDINARY;
  } else if (dt_lt(date, &(temporale->easter_date))) {
    season_info->season = CR_SEASON_LENT;
  } else if (dt_le(date, &(temporale->pentecost_date))) {
    season_info->season = CR_SEASON_EASTER;
  } else {
    season_info->season = CR_SEASON_ORDINARY;
  }

  // fake
  season_info->week = 0;
}
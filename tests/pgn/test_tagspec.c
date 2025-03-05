#include <criterion/criterion.h>

#include "pgn/tagspec.h"

Test(tagspec, tagspec_match)
{
        tagspec_t *spec = tagspec_new();
        cr_assert(tagspec_parse_line(spec, "Site"));
        cr_assert(tagspec_parse_line(spec, "WhiteElo"));
        cr_assert(tagspec_parse_line(spec, "BlackElo"));
        cr_assert(tagspec_parse_line(spec, "Ply > 3"));
        cr_assert(tagspec_parse_line(spec, "WhiteClock"));
        cr_assert(tagspec_parse_line(spec, "BlackClock"));
        cr_assert(tagspec_parse_line(spec, "WhiteTitle ! BOT"));
        cr_assert(tagspec_parse_line(spec, "BlackTitle ! BOT"));
        cr_assert(tagspec_parse_line(spec, "Result ! *"));
        cr_assert(tagspec_parse_line(spec, "Event = Rated Classical game"));

        cr_assert(tagspec_matches(spec, "Ply", "4"));
        cr_assert(!tagspec_matches(spec, "Ply", "3"));

        cr_assert(tagspec_matches(spec, "WhiteTitle", "HUMAN"));
        cr_assert(!tagspec_matches(spec, "WhiteTitle", "BOT"));

        cr_assert(tagspec_matches(spec, "Event", "Rated Classical game"));
        cr_assert(!tagspec_matches(spec, "Event", "Rated Bullet game"));

        tagspec_free(spec);
}

Test(tagspec, tagspec_parse_line)
{
        tagspec_t *spec = tagspec_new();
        cr_assert(tagspec_parse_line(spec, "BlackElo"));
        cr_assert_not_null(spec->tail);
        cr_expect_str_eq(spec->tail->name, "BlackElo");
        cr_expect_eq(spec->tail->kind, TAG_ALWAYS);

        cr_assert(tagspec_parse_line(spec, "Ply > 3"));
        cr_expect_str_eq(spec->tail->name, "Ply");
        cr_expect_eq(spec->tail->kind, TAG_GREATER_THAN);

        tagspec_free(spec);
}

Test(tagspec, tagspec_parse)
{
        tagspec_t *spec = tagspec_new();
        cr_assert(spec);

        cr_assert(tagspec_parse_line(spec, "Result ! *"));
        cr_assert_eq(spec->tail->kind, TAG_NOT_EQUALS);
        cr_assert_str_eq(spec->tail->value, "*");
        cr_assert_str_eq(spec->order_tail->name, "Result");

        cr_assert_eq(spec->order_head, spec->order_tail);

        cr_assert(tagspec_parse_line(spec, "Event = Rated Classical game"));
        cr_assert_eq(spec->tail->kind, TAG_EQUALS);
        cr_assert_str_eq(spec->tail->value, "Rated Classical game");

        cr_assert(tagspec_parse_line(spec, "Site      "));
        cr_assert_str_eq(spec->order_tail->name, "Site");
        cr_assert_str_neq(spec->tail->name, "Site");

        cr_assert(tagspec_parse_line(spec, "Ply > 2"));
        cr_assert_eq(spec->tail->kind, TAG_GREATER_THAN);
        cr_assert_str_eq(spec->tail->value, "2");

        tagspec_free(spec);
}

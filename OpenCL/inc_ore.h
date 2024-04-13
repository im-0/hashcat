#ifndef INC_ORE_H
#define INC_ORE_H

// vliw1

#define CHECK_LE(h0,h1,h2,h3,h4,h5,h6,h7)                                                                   \
  (                                                                                                         \
        ((h0)  < search[0])                                                                                 \
    || (((h0) == search[0]) && ((h1)  < search[1]))                                                         \
    || (((h0) == search[0]) && ((h1) == search[1]) && ((h2)  < search[2]))                                  \
    || (((h0) == search[0]) && ((h1) == search[1]) && ((h2) == search[2]) && ((h3)  < search[3]))           \
    || (((h0) == search[0]) && ((h1) == search[1]) && ((h2) == search[2]) && ((h3) == search[3]) && ((h4)  < search[4])) \
    || (((h0) == search[0]) && ((h1) == search[1]) && ((h2) == search[2]) && ((h3) == search[3]) && ((h4) == search[4]) && ((h5)  < search[5])) \
    || (((h0) == search[0]) && ((h1) == search[1]) && ((h2) == search[2]) && ((h3) == search[3]) && ((h4) == search[4]) && ((h5) == search[5]) && ((h6)  < search[6])) \
    || (((h0) == search[0]) && ((h1) == search[1]) && ((h2) == search[2]) && ((h3) == search[3]) && ((h4) == search[4]) && ((h5) == search[5]) && ((h6) == search[6]) && ((h7) <= search[7])) \
  )

#if VECT_SIZE == 1

#define CHECK_LE_S_SIMD(h0,h1,h2,h3,h4,h5,h6,h7)                                                            \
{                                                                                                           \
  if (CHECK_LE ((h0), (h1), (h2), (h3), (h4), (h5), (h6), (h7)))                                            \
  {                                                                                                         \
    const u32 final_hash_pos = DIGESTS_OFFSET_HOST + 0;                                                     \
                                                                                                            \
    if (hc_atomic_inc (&hashes_shown[final_hash_pos]) == 0)                                                 \
    {                                                                                                       \
      mark_hash (plains_buf, d_return_buf, SALT_POS_HOST, DIGESTS_CNT, 0, final_hash_pos, gid, il_pos, 0, 0); \
    }                                                                                                       \
  }                                                                                                         \
}

#endif

// vliw2

#if VECT_SIZE == 2

#define CHECK_LE_S_SIMD(h0,h1,h2,h3,h4,h5,h6,h7)                                                            \
{                                                                                                           \
  if (CHECK_LE ((h0).s0, (h1).s0, (h2).s0, (h3).s0, (h4).s0, (h5).s0, (h6).s0, (h7).s0))                    \
  {                                                                                                         \
    const u32 final_hash_pos = DIGESTS_OFFSET_HOST + 0;                                                     \
                                                                                                            \
    if (vector_accessible (il_pos, IL_CNT, 0) && (hc_atomic_inc (&hashes_shown[final_hash_pos]) == 0))      \
    {                                                                                                       \
      mark_hash (plains_buf, d_return_buf, SALT_POS_HOST, DIGESTS_CNT, 0, final_hash_pos, gid, il_pos + 0, 0, 0); \
    }                                                                                                       \
  }                                                                                                         \
                                                                                                            \
  if (CHECK_LE ((h0).s1, (h1).s1, (h2).s1, (h3).s1, (h4).s1, (h5).s1, (h6).s1, (h7).s1))                    \
  {                                                                                                         \
    const u32 final_hash_pos = DIGESTS_OFFSET_HOST + 0;                                                     \
                                                                                                            \
    if (vector_accessible (il_pos, IL_CNT, 1) && (hc_atomic_inc (&hashes_shown[final_hash_pos]) == 0))      \
    {                                                                                                       \
      mark_hash (plains_buf, d_return_buf, SALT_POS_HOST, DIGESTS_CNT, 0, final_hash_pos, gid, il_pos + 1, 0, 0); \
    }                                                                                                       \
  }                                                                                                         \
}

#endif

// vliw4

#if VECT_SIZE == 4

#define CHECK_LE_S_SIMD(h0,h1,h2,h3,h4,h5,h6,h7)                                                            \
{                                                                                                           \
  if (CHECK_LE ((h0).s0, (h1).s0, (h2).s0, (h3).s0, (h4).s0, (h5).s0, (h6).s0, (h7).s0))                    \
  {                                                                                                         \
    const u32 final_hash_pos = DIGESTS_OFFSET_HOST + 0;                                                     \
                                                                                                            \
    if (vector_accessible (il_pos, IL_CNT, 0) && (hc_atomic_inc (&hashes_shown[final_hash_pos]) == 0))      \
    {                                                                                                       \
      mark_hash (plains_buf, d_return_buf, SALT_POS_HOST, DIGESTS_CNT, 0, final_hash_pos, gid, il_pos + 0, 0, 0); \
    }                                                                                                       \
  }                                                                                                         \
                                                                                                            \
  if (CHECK_LE ((h0).s1, (h1).s1, (h2).s1, (h3).s1, (h4).s1, (h5).s1, (h6).s1, (h7).s1))                    \
  {                                                                                                         \
    const u32 final_hash_pos = DIGESTS_OFFSET_HOST + 0;                                                     \
                                                                                                            \
    if (vector_accessible (il_pos, IL_CNT, 1) && (hc_atomic_inc (&hashes_shown[final_hash_pos]) == 0))      \
    {                                                                                                       \
      mark_hash (plains_buf, d_return_buf, SALT_POS_HOST, DIGESTS_CNT, 0, final_hash_pos, gid, il_pos + 1, 0, 0); \
    }                                                                                                       \
  }                                                                                                         \
                                                                                                            \
  if (CHECK_LE ((h0).s2, (h1).s2, (h2).s2, (h3).s2, (h4).s2, (h5).s2, (h6).s2, (h7).s2))                    \
  {                                                                                                         \
    const u32 final_hash_pos = DIGESTS_OFFSET_HOST + 0;                                                     \
                                                                                                            \
    if (vector_accessible (il_pos, IL_CNT, 2) && (hc_atomic_inc (&hashes_shown[final_hash_pos]) == 0))      \
    {                                                                                                       \
      mark_hash (plains_buf, d_return_buf, SALT_POS_HOST, DIGESTS_CNT, 0, final_hash_pos, gid, il_pos + 2, 0, 0); \
    }                                                                                                       \
  }                                                                                                         \
                                                                                                            \
  if (CHECK_LE ((h0).s3, (h1).s3, (h2).s3, (h3).s3, (h4).s3, (h5).s3, (h6).s3, (h7).s3))                    \
  {                                                                                                         \
    const u32 final_hash_pos = DIGESTS_OFFSET_HOST + 0;                                                     \
                                                                                                            \
    if (vector_accessible (il_pos, IL_CNT, 3) && (hc_atomic_inc (&hashes_shown[final_hash_pos]) == 0))      \
    {                                                                                                       \
      mark_hash (plains_buf, d_return_buf, SALT_POS_HOST, DIGESTS_CNT, 0, final_hash_pos, gid, il_pos + 3, 0, 0); \
    }                                                                                                       \
  }                                                                                                         \
}

#endif

// vliw8

#if VECT_SIZE == 8

#define CHECK_LE_S_SIMD(h0,h1,h2,h3,h4,h5,h6,h7)                                                            \
{                                                                                                           \
  if (CHECK_LE ((h0).s0, (h1).s0, (h2).s0, (h3).s0, (h4).s0, (h5).s0, (h6).s0, (h7).s0))                    \
  {                                                                                                         \
    const u32 final_hash_pos = DIGESTS_OFFSET_HOST + 0;                                                     \
                                                                                                            \
    if (vector_accessible (il_pos, IL_CNT, 0) && (hc_atomic_inc (&hashes_shown[final_hash_pos]) == 0))      \
    {                                                                                                       \
      mark_hash (plains_buf, d_return_buf, SALT_POS_HOST, DIGESTS_CNT, 0, final_hash_pos, gid, il_pos + 0, 0, 0); \
    }                                                                                                       \
  }                                                                                                         \
                                                                                                            \
  if (CHECK_LE ((h0).s1, (h1).s1, (h2).s1, (h3).s1, (h4).s1, (h5).s1, (h6).s1, (h7).s1))                    \
  {                                                                                                         \
    const u32 final_hash_pos = DIGESTS_OFFSET_HOST + 0;                                                     \
                                                                                                            \
    if (vector_accessible (il_pos, IL_CNT, 1) && (hc_atomic_inc (&hashes_shown[final_hash_pos]) == 0))      \
    {                                                                                                       \
      mark_hash (plains_buf, d_return_buf, SALT_POS_HOST, DIGESTS_CNT, 0, final_hash_pos, gid, il_pos + 1, 0, 0); \
    }                                                                                                       \
  }                                                                                                         \
                                                                                                            \
  if (CHECK_LE ((h0).s2, (h1).s2, (h2).s2, (h3).s2, (h4).s2, (h5).s2, (h6).s2, (h7).s2))                    \
  {                                                                                                         \
    const u32 final_hash_pos = DIGESTS_OFFSET_HOST + 0;                                                     \
                                                                                                            \
    if (vector_accessible (il_pos, IL_CNT, 2) && (hc_atomic_inc (&hashes_shown[final_hash_pos]) == 0))      \
    {                                                                                                       \
      mark_hash (plains_buf, d_return_buf, SALT_POS_HOST, DIGESTS_CNT, 0, final_hash_pos, gid, il_pos + 2, 0, 0); \
    }                                                                                                       \
  }                                                                                                         \
                                                                                                            \
  if (CHECK_LE ((h0).s3, (h1).s3, (h2).s3, (h3).s3, (h4).s3, (h5).s3, (h6).s3, (h7).s3))                    \
  {                                                                                                         \
    const u32 final_hash_pos = DIGESTS_OFFSET_HOST + 0;                                                     \
                                                                                                            \
    if (vector_accessible (il_pos, IL_CNT, 3) && (hc_atomic_inc (&hashes_shown[final_hash_pos]) == 0))      \
    {                                                                                                       \
      mark_hash (plains_buf, d_return_buf, SALT_POS_HOST, DIGESTS_CNT, 0, final_hash_pos, gid, il_pos + 3, 0, 0); \
    }                                                                                                       \
  }                                                                                                         \

  if (CHECK_LE ((h0).s4, (h1).s4, (h2).s4, (h3).s4, (h4).s4, (h5).s4, (h6).s4, (h7).s4))                    \
  {                                                                                                         \
    const u32 final_hash_pos = DIGESTS_OFFSET_HOST + 0;                                                     \
                                                                                                            \
    if (vector_accessible (il_pos, IL_CNT, 4) && (hc_atomic_inc (&hashes_shown[final_hash_pos]) == 0))      \
    {                                                                                                       \
      mark_hash (plains_buf, d_return_buf, SALT_POS_HOST, DIGESTS_CNT, 0, final_hash_pos, gid, il_pos + 4, 0, 0); \
    }                                                                                                       \
  }                                                                                                         \
                                                                                                            \
  if (CHECK_LE ((h0).s5, (h1).s5, (h2).s5, (h3).s5, (h4).s5, (h5).s5, (h6).s5, (h7).s5))                    \
  {                                                                                                         \
    const u32 final_hash_pos = DIGESTS_OFFSET_HOST + 0;                                                     \
                                                                                                            \
    if (vector_accessible (il_pos, IL_CNT, 5) && (hc_atomic_inc (&hashes_shown[final_hash_pos]) == 0))      \
    {                                                                                                       \
      mark_hash (plains_buf, d_return_buf, SALT_POS_HOST, DIGESTS_CNT, 0, final_hash_pos, gid, il_pos + 5, 0, 0); \
    }                                                                                                       \
  }                                                                                                         \
                                                                                                            \
  if (CHECK_LE ((h0).s6, (h1).s6, (h2).s6, (h3).s6, (h4).s6, (h5).s6, (h6).s6, (h7).s6))                    \
  {                                                                                                         \
    const u32 final_hash_pos = DIGESTS_OFFSET_HOST + 0;                                                     \
                                                                                                            \
    if (vector_accessible (il_pos, IL_CNT, 6) && (hc_atomic_inc (&hashes_shown[final_hash_pos]) == 0))      \
    {                                                                                                       \
      mark_hash (plains_buf, d_return_buf, SALT_POS_HOST, DIGESTS_CNT, 0, final_hash_pos, gid, il_pos + 6, 0, 0); \
    }                                                                                                       \
  }                                                                                                         \
                                                                                                            \
  if (CHECK_LE ((h0).s7, (h1).s7, (h2).s7, (h3).s7, (h4).s7, (h5).s7, (h6).s7, (h7).s7))                    \
  {                                                                                                         \
    const u32 final_hash_pos = DIGESTS_OFFSET_HOST + 0;                                                     \
                                                                                                            \
    if (vector_accessible (il_pos, IL_CNT, 7) && (hc_atomic_inc (&hashes_shown[final_hash_pos]) == 0))      \
    {                                                                                                       \
      mark_hash (plains_buf, d_return_buf, SALT_POS_HOST, DIGESTS_CNT, 0, final_hash_pos, gid, il_pos + 7, 0, 0); \
    }                                                                                                       \
  }                                                                                                         \
}

#endif

// vliw16

#if VECT_SIZE == 16

#define CHECK_LE_S_SIMD(h0,h1,h2,h3,h4,h5,h6,h7)                                                            \
{                                                                                                           \
  if (CHECK_LE ((h0).s0, (h1).s0, (h2).s0, (h3).s0, (h4).s0, (h5).s0, (h6).s0, (h7).s0))                    \
  {                                                                                                         \
    const u32 final_hash_pos = DIGESTS_OFFSET_HOST + 0;                                                     \
                                                                                                            \
    if (vector_accessible (il_pos, IL_CNT, 0) && (hc_atomic_inc (&hashes_shown[final_hash_pos]) == 0))      \
    {                                                                                                       \
      mark_hash (plains_buf, d_return_buf, SALT_POS_HOST, DIGESTS_CNT, 0, final_hash_pos, gid, il_pos + 0, 0, 0); \
    }                                                                                                       \
  }                                                                                                         \
                                                                                                            \
  if (CHECK_LE ((h0).s1, (h1).s1, (h2).s1, (h3).s1, (h4).s1, (h5).s1, (h6).s1, (h7).s1))                    \
  {                                                                                                         \
    const u32 final_hash_pos = DIGESTS_OFFSET_HOST + 0;                                                     \
                                                                                                            \
    if (vector_accessible (il_pos, IL_CNT, 1) && (hc_atomic_inc (&hashes_shown[final_hash_pos]) == 0))      \
    {                                                                                                       \
      mark_hash (plains_buf, d_return_buf, SALT_POS_HOST, DIGESTS_CNT, 0, final_hash_pos, gid, il_pos + 1, 0, 0); \
    }                                                                                                       \
  }                                                                                                         \
                                                                                                            \
  if (CHECK_LE ((h0).s2, (h1).s2, (h2).s2, (h3).s2, (h4).s2, (h5).s2, (h6).s2, (h7).s2))                    \
  {                                                                                                         \
    const u32 final_hash_pos = DIGESTS_OFFSET_HOST + 0;                                                     \
                                                                                                            \
    if (vector_accessible (il_pos, IL_CNT, 2) && (hc_atomic_inc (&hashes_shown[final_hash_pos]) == 0))      \
    {                                                                                                       \
      mark_hash (plains_buf, d_return_buf, SALT_POS_HOST, DIGESTS_CNT, 0, final_hash_pos, gid, il_pos + 2, 0, 0); \
    }                                                                                                       \
  }                                                                                                         \
                                                                                                            \
  if (CHECK_LE ((h0).s3, (h1).s3, (h2).s3, (h3).s3, (h4).s3, (h5).s3, (h6).s3, (h7).s3))                    \
  {                                                                                                         \
    const u32 final_hash_pos = DIGESTS_OFFSET_HOST + 0;                                                     \
                                                                                                            \
    if (vector_accessible (il_pos, IL_CNT, 3) && (hc_atomic_inc (&hashes_shown[final_hash_pos]) == 0))      \
    {                                                                                                       \
      mark_hash (plains_buf, d_return_buf, SALT_POS_HOST, DIGESTS_CNT, 0, final_hash_pos, gid, il_pos + 3, 0, 0); \
    }                                                                                                       \
  }                                                                                                         \
  if (CHECK_LE ((h0).s4, (h1).s4, (h2).s4, (h3).s4, (h4).s4, (h5).s4, (h6).s4, (h7).s4))                    \
  {                                                                                                         \
    const u32 final_hash_pos = DIGESTS_OFFSET_HOST + 0;                                                     \
                                                                                                            \
    if (vector_accessible (il_pos, IL_CNT, 4) && (hc_atomic_inc (&hashes_shown[final_hash_pos]) == 0))      \
    {                                                                                                       \
      mark_hash (plains_buf, d_return_buf, SALT_POS_HOST, DIGESTS_CNT, 0, final_hash_pos, gid, il_pos + 4, 0, 0); \
    }                                                                                                       \
  }                                                                                                         \
                                                                                                            \
  if (CHECK_LE ((h0).s5, (h1).s5, (h2).s5, (h3).s5, (h4).s5, (h5).s5, (h6).s5, (h7).s5))                    \
  {                                                                                                         \
    const u32 final_hash_pos = DIGESTS_OFFSET_HOST + 0;                                                     \
                                                                                                            \
    if (vector_accessible (il_pos, IL_CNT, 5) && (hc_atomic_inc (&hashes_shown[final_hash_pos]) == 0))      \
    {                                                                                                       \
      mark_hash (plains_buf, d_return_buf, SALT_POS_HOST, DIGESTS_CNT, 0, final_hash_pos, gid, il_pos + 5, 0, 0); \
    }                                                                                                       \
  }                                                                                                         \
                                                                                                            \
  if (CHECK_LE ((h0).s6, (h1).s6, (h2).s6, (h3).s6, (h4).s6, (h5).s6, (h6).s6, (h7).s6))                    \
  {                                                                                                         \
    const u32 final_hash_pos = DIGESTS_OFFSET_HOST + 0;                                                     \
                                                                                                            \
    if (vector_accessible (il_pos, IL_CNT, 6) && (hc_atomic_inc (&hashes_shown[final_hash_pos]) == 0))      \
    {                                                                                                       \
      mark_hash (plains_buf, d_return_buf, SALT_POS_HOST, DIGESTS_CNT, 0, final_hash_pos, gid, il_pos + 6, 0, 0); \
    }                                                                                                       \
  }                                                                                                         \
                                                                                                            \
  if (CHECK_LE ((h0).s7, (h1).s7, (h2).s7, (h3).s7, (h4).s7, (h5).s7, (h6).s7, (h7).s7))                    \
  {                                                                                                         \
    const u32 final_hash_pos = DIGESTS_OFFSET_HOST + 0;                                                     \
                                                                                                            \
    if (vector_accessible (il_pos, IL_CNT, 7) && (hc_atomic_inc (&hashes_shown[final_hash_pos]) == 0))      \
    {                                                                                                       \
      mark_hash (plains_buf, d_return_buf, SALT_POS_HOST, DIGESTS_CNT, 0, final_hash_pos, gid, il_pos + 7, 0, 0); \
    }                                                                                                       \
  }                                                                                                         \
                                                                                                            \
  if (CHECK_LE ((h0).s8, (h1).s8, (h2).s8, (h3).s8, (h4).s8, (h5).s8, (h6).s8, (h7).s8))                    \
  {                                                                                                         \
    const u32 final_hash_pos = DIGESTS_OFFSET_HOST + 0;                                                     \
                                                                                                            \
    if (vector_accessible (il_pos, IL_CNT, 8) && (hc_atomic_inc (&hashes_shown[final_hash_pos]) == 0))      \
    {                                                                                                       \
      mark_hash (plains_buf, d_return_buf, SALT_POS_HOST, DIGESTS_CNT, 0, final_hash_pos, gid, il_pos + 8, 0, 0); \
    }                                                                                                       \
  }                                                                                                         \
                                                                                                            \
  if (CHECK_LE ((h0).s9, (h1).s9, (h2).s9, (h3).s9, (h4).s9, (h5).s9, (h6).s9, (h7).s9))                    \
  {                                                                                                         \
    const u32 final_hash_pos = DIGESTS_OFFSET_HOST + 0;                                                     \
                                                                                                            \
    if (vector_accessible (il_pos, IL_CNT, 9) && (hc_atomic_inc (&hashes_shown[final_hash_pos]) == 0))      \
    {                                                                                                       \
      mark_hash (plains_buf, d_return_buf, SALT_POS_HOST, DIGESTS_CNT, 0, final_hash_pos, gid, il_pos + 9, 0, 0); \
    }                                                                                                       \
  }                                                                                                         \
                                                                                                            \
  if (CHECK_LE ((h0).sa, (h1).sa, (h2).sa, (h3).sa, (h4).sa, (h5).sa, (h6).sa, (h7).sa))                    \
  {                                                                                                         \
    const u32 final_hash_pos = DIGESTS_OFFSET_HOST + 0;                                                     \
                                                                                                            \
    if (vector_accessible (il_pos, IL_CNT, 10) && (hc_atomic_inc (&hashes_shown[final_hash_pos]) == 0))     \
    {                                                                                                       \
      mark_hash (plains_buf, d_return_buf, SALT_POS_HOST, DIGESTS_CNT, 0, final_hash_pos, gid, il_pos + 10, 0, 0); \
    }                                                                                                       \
  }                                                                                                         \
                                                                                                            \
  if (CHECK_LE ((h0).sb, (h1).sb, (h2).sb, (h3).sb, (h4).sb, (h5).sb, (h6).sb, (h7).sb))                    \
  {                                                                                                         \
    const u32 final_hash_pos = DIGESTS_OFFSET_HOST + 0;                                                     \
                                                                                                            \
    if (vector_accessible (il_pos, IL_CNT, 11) && (hc_atomic_inc (&hashes_shown[final_hash_pos]) == 0))     \
    {                                                                                                       \
      mark_hash (plains_buf, d_return_buf, SALT_POS_HOST, DIGESTS_CNT, 0, final_hash_pos, gid, il_pos + 11, 0, 0); \
    }                                                                                                       \
  }                                                                                                         \
                                                                                                            \
  if (CHECK_LE ((h0).sc, (h1).sc, (h2).sc, (h3).sc, (h4).sc, (h5).sc, (h6).sc, (h7).sc))                    \
  {                                                                                                         \
    const u32 final_hash_pos = DIGESTS_OFFSET_HOST + 0;                                                     \
                                                                                                            \
    if (vector_accessible (il_pos, IL_CNT, 12) && (hc_atomic_inc (&hashes_shown[final_hash_pos]) == 0))     \
    {                                                                                                       \
      mark_hash (plains_buf, d_return_buf, SALT_POS_HOST, DIGESTS_CNT, 0, final_hash_pos, gid, il_pos + 12, 0, 0); \
    }                                                                                                       \
  }                                                                                                         \
                                                                                                            \
  if (CHECK_LE ((h0).sd, (h1).sd, (h2).sd, (h3).sd, (h4).sd, (h5).sd, (h6).sd, (h7).sd))                    \
  {                                                                                                         \
    const u32 final_hash_pos = DIGESTS_OFFSET_HOST + 0;                                                     \
                                                                                                            \
    if (vector_accessible (il_pos, IL_CNT, 13) && (hc_atomic_inc (&hashes_shown[final_hash_pos]) == 0))     \
    {                                                                                                       \
      mark_hash (plains_buf, d_return_buf, SALT_POS_HOST, DIGESTS_CNT, 0, final_hash_pos, gid, il_pos + 13, 0, 0); \
    }                                                                                                       \
  }                                                                                                         \
                                                                                                            \
  if (CHECK_LE ((h0).se, (h1).se, (h2).se, (h3).se, (h4).se, (h5).se, (h6).se, (h7).se))                    \
  {                                                                                                         \
    const u32 final_hash_pos = DIGESTS_OFFSET_HOST + 0;                                                     \
                                                                                                            \
    if (vector_accessible (il_pos, IL_CNT, 14) && (hc_atomic_inc (&hashes_shown[final_hash_pos]) == 0))     \
    {                                                                                                       \
      mark_hash (plains_buf, d_return_buf, SALT_POS_HOST, DIGESTS_CNT, 0, final_hash_pos, gid, il_pos + 14, 0, 0); \
    }                                                                                                       \
  }                                                                                                         \
                                                                                                            \
  if (CHECK_LE ((h0).sf, (h1).sf, (h2).sf, (h3).sf, (h4).sf, (h5).sf, (h6).sf, (h7).sf))                    \
  {                                                                                                         \
    const u32 final_hash_pos = DIGESTS_OFFSET_HOST + 0;                                                     \
                                                                                                            \
    if (vector_accessible (il_pos, IL_CNT, 15) && (hc_atomic_inc (&hashes_shown[final_hash_pos]) == 0))     \
    {                                                                                                       \
      mark_hash (plains_buf, d_return_buf, SALT_POS_HOST, DIGESTS_CNT, 0, final_hash_pos, gid, il_pos + 15, 0, 0); \
    }                                                                                                       \
  }                                                                                                         \
}

#endif

#endif

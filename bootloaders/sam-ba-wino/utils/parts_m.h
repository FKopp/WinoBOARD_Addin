/**
 * \file
 *
 * \brief Atmel part identification macros
 *
 * Copyright (C) 2012-2014 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */

#ifndef ATMEL_PARTS_H
#define ATMEL_PARTS_H

/**
 * \defgroup part_macros_group Atmel part identification macros
 *
 * This collection of macros identify which series and families that the various
 * Atmel parts belong to. These can be used to select part-dependent sections of
 * code at compile time.
 *
 * @{
 */

/**
 * \name Convenience macros for part checking
 * @{
 */
/* ! Check GCC and IAR part definition for SAM */
#define SAM_PART_IS_DEFINED(part) (defined(__ ## part ## __))
/** @} */

/**
 * \name SAMD21 series
 * @{
 */
#define SAMD21J ( \
		SAM_PART_IS_DEFINED(SAMD21J15A) || \
		SAM_PART_IS_DEFINED(SAMD21J16A) || \
		SAM_PART_IS_DEFINED(SAMD21J17A) || \
		SAM_PART_IS_DEFINED(SAMD21J18A) \
	)

#define SAMD21G ( \
		SAM_PART_IS_DEFINED(SAMD21G15A) || \
		SAM_PART_IS_DEFINED(SAMD21G16A) || \
		SAM_PART_IS_DEFINED(SAMD21G17A) || \
		SAM_PART_IS_DEFINED(SAMD21G18A) \
	)

#define SAMD21E ( \
		SAM_PART_IS_DEFINED(SAMD21E15A) || \
		SAM_PART_IS_DEFINED(SAMD21E16A) || \
		SAM_PART_IS_DEFINED(SAMD21E17A) || \
		SAM_PART_IS_DEFINED(SAMD21E18A) \
	)
/** @} */

/**
 * \name SAM families
 * @{
 */
/** SAMD Family */
#define SAMD   (SAMD20 || SAMD21 || SAMD10 || SAMD11)

/** SAM0 product line (cortex-m0+) */
#define SAM0 (SAMD20 || SAMD21 || SAMR21 || SAMD10 || SAMD11)

/** @} */

/** SAM product line */
#define SAM (SAM3S || SAM3U || SAM3N || SAM3XA || SAM4S || SAM4L || SAM4E || \
		SAM0 || SAM4N || SAM4C || SAM4CM || SAM4CP || SAMG)

/** @} */

/** @} */

/** @} */

#endif /* ATMEL_PARTS_H */

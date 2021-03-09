/*-
 * SPDX-License-Identifier: BSD-2-Clause-FreeBSD
 *
 * Copyright (C) 2021 Tobias Kortkamp <tobik@FreeBSD.org>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/*
 * Test for get_current_dir_name().
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <atf-c.h>

ATF_TC_WITHOUT_HEAD(get_current_dir_name_test);
ATF_TC_BODY(get_current_dir_name_test, tc)
{

	unsetenv("PWD");
	char *pwd = getcwd(NULL, 0);
	ATF_REQUIRE_STREQ(get_current_dir_name(), pwd);

	putenv("PWD=/nonexistent");
	ATF_REQUIRE_STREQ(get_current_dir_name(), pwd);

	putenv("PWD=.");
	ATF_REQUIRE_STREQ(get_current_dir_name(), ".");

	symlink("../../tests/stdlib", "foo");
	setenv("PWD", "../../tests/stdlib/foo", 1);
	ATF_REQUIRE_STREQ(get_current_dir_name(), "../../tests/stdlib/foo");
	unlink("foo");
}

ATF_TP_ADD_TCS(tp)
{

	ATF_TP_ADD_TC(tp, get_current_dir_name_test);

	return (atf_no_error());
}

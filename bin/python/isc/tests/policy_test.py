############################################################################
# Copyright (C) 2013-2015  Internet Systems Consortium, Inc. ("ISC")
#
# Permission to use, copy, modify, and/or distribute this software for any
# purpose with or without fee is hereby granted, provided that the above
# copyright notice and this permission notice appear in all copies.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
# REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
# AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
# INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
# LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
# OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
# PERFORMANCE OF THIS SOFTWARE.
############################################################################

import sys
import unittest
sys.path.append('../..')
from isc import *


class PolicyTest(unittest.TestCase):
    def test_keysize(self):
        pol = policy.dnssec_policy()
        pol.load('test-policies/01-keysize.pol')
        self.assertEqual(pol.policy('good_rsa.test').get_name(),
                         "good_rsa.test")
        self.assertEqual(pol.policy('good_rsa.test').constructed(), False)
        self.assertEqual(pol.policy('good_rsa.test').validate(), (True, ""))
        self.assertEqual(pol.policy('good_dsa.test').get_name(),
                         "good_dsa.test")
        self.assertEqual(pol.policy('good_dsa.test').constructed(), False)
        self.assertEqual(pol.policy('good_dsa.test').validate(), (True, ""))

        self.assertEqual(pol.policy('bad_dsa.test').validate(),
                         (False, 'Key size not a divisible by 64'))

    def test_prepublish(self):
        pol = policy.dnssec_policy()
        pol.load('test-policies/02-prepublish.pol')
        pol_name = 'good_prepublish.test'
        # print(pol.policy(pol_name))
        self.assertEqual(pol.policy(pol_name).validate(),
                         (True, ""))
        pol_name = 'bad_prepublish.test'
        # print(pol.policy(pol_name))
        self.assertEqual(pol.policy(pol_name).validate(),
                         (False, 'KSK pre publish period exceeds rollover '
                                 'period'))

    def test_postpublish(self):
        pol = policy.dnssec_policy()
        pol.load('test-policies/03-postpublish.pol')
        self.assertEqual(pol.policy('good_postpublish.test').validate(),
                         (True, ""))
        self.assertEqual(pol.policy('bad_postpublish.test').validate(),
                         (False, 'KSK pre publish period exceeds rollover '
                                 'period'))

    def test_combined_pre_post(self):
        pol = policy.dnssec_policy()
        pol.load('test-policies/04-combined-pre-post.pol')
        pol_name = 'good_combined_pre_post_ksk.test'
        # print(pol.policy(pol_name))
        self.assertEqual(pol.policy(pol_name).validate(),
                         (True, ""))
        pol_name = 'bad_combined_pre_post_ksk.test'
        # print(pol.policy(pol_name))
        self.assertEqual(pol.policy(pol_name).validate(),
                         (False, 'KSK pre+post publish periods exceed '
                                 'rollover period'))
        pol_name = 'good_combined_pre_post_zsk.test'
        # print(pol.policy(pol_name))
        self.assertEqual(pol.policy(pol_name).validate(),
                         (True, ""))
        pol_name = 'bad_combined_pre_post_zsk.test'
        # print(pol.policy(pol_name))
        self.assertEqual(pol.policy(pol_name).validate(),
                         (False, 'ZSK pre+post publish periods exceed '
                                 'rollover period'))

if __name__ == "__main__":
    unittest.main()

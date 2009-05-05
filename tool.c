/* tool.c --- Command line interface to libykclient.
 *
 * Written by Simon Josefsson <simon@josefsson.org>.
 * Copyright (c) 2006, 2007, 2008, 2009 Yubico AB
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *    * Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *
 *    * Redistributions in binary form must reproduce the above
 *      copyright notice, this list of conditions and the following
 *      disclaimer in the documentation and/or other materials provided
 *      with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include "ykclient.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

int
main (int argc, char *argv[])
{
  char *client_id, *token;
  int ret;

  /* Parse command line parameters. */
  if (argc != 3)
    {
      printf ("Usage: %s <client_id> <yubikey_otp>\n", argv[0]);
      printf (" CLIENT_ID: your client id integer\n");
      printf (" YUBIKEY_OTP: One-time password generated by yubikey\n");
      return EXIT_FAILURE;
    }

  client_id = argv[1];
  token = argv[2];

  if (atoi (client_id) <= 0)
    {
      printf ("error: client identity must be a non-zero integer.\n");
      return EXIT_FAILURE;
    }

  if (strlen (token) < 32)
    {
      printf ("error: ModHex encoded token must be at least 32 characters.\n");
      return EXIT_FAILURE;
    }

  /* Debug. */
  printf ("Input:\n");
  printf ("  client id: %d\n", atoi (client_id));
  printf ("  token: %s\n", token);

  ret = ykclient_verify_otp (token, atoi (client_id), NULL);

  printf ("Verification output (%d): %s\n", ret, ykclient_strerror (ret));

  if (ret != YKCLIENT_OK)
    return EXIT_FAILURE;

  return EXIT_SUCCESS;
}
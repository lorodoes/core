<?php
/**
 *    Copyright (C) 2016 Deciso B.V.
 *
 *    All rights reserved.
 *
 *    Redistribution and use in source and binary forms, with or without
 *    modification, are permitted provided that the following conditions are met:
 *
 *    1. Redistributions of source code must retain the above copyright notice,
 *       this list of conditions and the following disclaimer.
 *
 *    2. Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *
 *    THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES,
 *    INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 *    AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *    AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
 *    OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *    SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *    INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *    CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *    ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *    POSSIBILITY OF SUCH DAMAGE.
 *
 */

function filter_core_bootstrap($fw)
{
    global $config;
    // set defaults
    $filter_rule_defaults = array();
    $filter_rule_defaults['pass'] = array("type" => "pass", "log" => !isset($config['syslog']['nologdefaultpass']));
    $filter_rule_defaults['block'] = array("type" => "block", "log" => !isset($config['syslog']['nologdefaultblock']));

    // setup system filter rules
    filter_core_rules_system($fw, $filter_rule_defaults);
}

/**
 *  core system rules
 */
function filter_core_rules_system($fw, $defaults)
{
    global $config;

    // block All IPv6 except loopback traffic
    $fw->registerFilterRule(1,
      array('interface' => 'loopback', 'ipprotocol'=>'inet6', 'disabled' => isset($config['system']['ipv6allow']),
          'label' => 'Pass all loopback IPv6'),
      $defaults['pass']
    );
    $fw->registerFilterRule(1,
      array('ipprotocol'=>'inet6','label' => 'Block all IPv6', 'disabled' => isset($config['system']['ipv6allow'])),
      $defaults['block']
    );
}
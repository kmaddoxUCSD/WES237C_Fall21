set SynModuleInfo {
  {SRCNAME fir MODELNAME fir RTLNAME fir IS_TOP 1
    SUBMODULES {
      {MODELNAME fir_mac_muladd_5s_10s_10ns_10_4_1 RTLNAME fir_mac_muladd_5s_10s_10ns_10_4_1 BINDTYPE op TYPE add IMPL dsp LATENCY 3 ALLOW_PRAGMA 1}
      {MODELNAME fir_shift_reg_V RTLNAME fir_shift_reg_V BINDTYPE storage TYPE ram IMPL auto LATENCY 2 ALLOW_PRAGMA 1}
      {MODELNAME fir_c RTLNAME fir_c BINDTYPE storage TYPE rom IMPL auto LATENCY 2 ALLOW_PRAGMA 1}
      {MODELNAME fir_control_s_axi RTLNAME fir_control_s_axi BINDTYPE interface TYPE interface_s_axilite}
      {MODELNAME fir_gmem_m_axi RTLNAME fir_gmem_m_axi BINDTYPE interface TYPE interface_m_axi}
    }
  }
}

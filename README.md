# IParameter
A strong typed parameter definition

Example of use:
  
  `IParameterLisa2Helper<int> terminalIdentification( LISA2_100000_TERMINAL_IDENTIFICATION, 100 );`  
  `DebugWriteF( DebugSourceAlways, "terminalIdentification = %d\n", terminalIdentification.get() );`

  terminalIdentification is a descendant of IParameter<int>, and can thus be passed to functions, without them knowing the source of the parameter.

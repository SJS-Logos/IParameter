# IParameter
A type strong parameter definition

Example of use:
  IParameterLisa2Helper<int> terminalIdentification( LISA2_100000_TERMINAL_IDENTIFICATION, 100 );
  DebugWriteF( DebugSourceAlways, "terminalIdentification = %d\n", terminalIdentification.get() );

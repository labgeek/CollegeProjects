
Program Russe10(INPUT, OUTPUT);
(***************************************************************************)
(* Russe is a variation of the multiplication algorithm used in computers  *)
(*    * the algorithm comes directly from "Fund. of Algorithms," by B&B    *)
(*    * Russe4 adds post-conditions                                        *)
(*    * Russe5 cycles thru "K" iterations(tests)                           *)
(*    * Russe9 adds "I" & "J" to facilitate loop invariant                 *)
(*    * Russe10 adds triangular profiles and Print_Levels                  *)
(*                                                                         *}
(***************************************************************************)
Uses CRT;                     {needed to support ClrScr proc in Turbo Pascal}
Label 9;                          {label always used for "fast escape GOTOs"}
Const
  LARGEST_MorN = 200;            {named constants promote single pt. control}
Type
  SUBRANGE_MorN = 0..LARGEST_MorN;             {need "type" to pass to procs}
  SUBRANGE1MIL = 0..LARGEST_Morn*LARGEST_MorN; {need "type" to pass to procs}
Var
  ANSWER, FAILURES, K, ITERATIONS : INTEGER;              {variables in main}
  M0, N0, ORACLE : SUBRANGE1MIL;    {recog. the target machine & info hiding}
  X, Y : REAL;
  PRINT_LEVEL : 0..3;
(**************************************************)
Function Result2(M {in}, N {in}: Integer): Integer;
Var Result : Integer;     {multiplication > 2^15-1 will PURPOSELY fail here}
       I,J : Integer;    {introduces loop counters to facilitate assertions}
Begin
     {M0 and N0 IN [0..LARGEST_MorN]  <= preconditions}
     Result:=0;  I:=0; J:=0;
     Repeat
       IF ODD(M) THEN begin  Result:=Result+N; I:=I+1  end;       {IF ODD(M)}
       J := J + 1; {neither J nor I needed for Russe, but for the assertions}
       M := M DIV 2;
       N := N + N;  
       {M >= 0 and N=N0*2^J and Result = ? }
       {  ... this is the loop invariant; M & N can be}
       {more strongly specified; add a loop counter, say "I" & "J" }
       {to simplify the formulation of "N" and "Result"}
       {writeln('I,J,N0,N, and Result= ',I:4,J:4,N0:8, N:8, Result:8);}
     Until M=0;                 {M=1 was a fault in original encoding of B&B}
     Result2 := Result;
     {M=0 and Result2=Result=M0*N0 and N=N0*2^J; <= post-conditions
                                       ...also, better to use a WHILE loop?}
End;
(***************************************************)

begin (*main*)
  {$R+}                              {enables "sub-range-checking" in turbo}
  FAILURES := 0;                                        {initialize to zero}
  ClrScr;                              {non-Standard, requires the CRT Unit}
  Randomize;      {initiates the pseudo-RNG -- triggered via the system clk}
  PRINT_LEVEL := 1;                   {print out all successes AND failures}
  WRITELN('How many Iterations(tests of Russe)?');
  READLN(ITERATIONS);
  WRITELN;
  FOR K := 1 TO ITERATIONS DO BEGIN
    X := LARGEST_MorN*(1-SQRT(1-RANDOM));
    M0 := TRUNC(X);
    Y := LARGEST_MorN*(1-SQRT(1-RANDOM));
    N0 := TRUNC(Y);
    IF PRINT_LEVEL=1 THEN                {PRINT_LEVEL=0 only shows failures}
      WRITELN(M0:4,N0:4,'  ===> ',M0*N0:4);
  {M0 and/or N0 must be >= 0 AND M0*N0 must not be > 1M}
    IF (M0 OR N0 < 0) THEN BEGIN
    WRITELN('assertion error, M0 and/or N0 <= 0');        {sample assertion}
    WRITELN('Press "enter" to return to program');
    READLN;         {this holds the output screen in TURBO 6.0 until RETURN}
    GOTO 9;                                          {McCracken's "Get Out"}
    END; {end IF assertion check}

    ANSWER := Result2(M0,N0);
    ORACLE := M0*N0;
  IF (ANSWER <> ORACLE) THEN BEGIN
    WRITELN('Russe yields ANSWER= ',ANSWER,  '  .... Check it against ORACLE=',ORACLE);
     {note M0*N0 computes as a "sub-range" type & doesnot blow up as fast}
    WRITELN;
    FAILURES := FAILURES + 1;
    WRITELN('# of FAILURES= ',FAILURES:4,' ... Estmated SW Reliability= ',
                  1-Failures/Iterations:8:4);
    WRITELN('===========================================================');
  END;{IF}
  END;{FOR}
  WRITELN;
  WRITELN('Final # of failures= ',failures:3,';  Final SW Reliability= ',(1-Failures/Iterations):8:4);
  WRITELN('----------------------------------------------------------------');
  WRITELN('This completes the calculations and screen print!');
  WRITELN('Press "enter" to return to program');
  READLN;            {this holds the output screen in TURBO 6.0 until RETURN}
9:   {jumps here only from "get out" GOTOs}
end. {*main*}

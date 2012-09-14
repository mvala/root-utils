#ifndef __CINT__
#include <TProofBench.h>
#include <TProof.h>
#endif
void GenerateFiles(const char* proof="lite://",const char *dsName="myDS") {
   TProofBench pb(proof, "test.root");
   if (gProof->UploadPackage("ProofBenchDataSel.par")) return;
   if (gProof->EnablePackage("ProofBenchDataSel")) return;
   pb.MakeDataSet(dsName, 10000);
}

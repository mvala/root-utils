#include <TSystem.h>
#include <TCollection.h>
#include <TFileCollection.h>
#include <TFileInfo.h>
#include <THashList.h>
#include <TProof.h>
#include <TFile.h>

#include "TPeacVerifierSel.h"

TPeacVerifierSel::TPeacVerifierSel(TTree * /*tree*/) : TSelector(),fChain(0),fPrefix("/pool/data/01/xrdnamespace"),fFcIn(0),fFcOut(0)
{

}

Bool_t TPeacVerifierSel::Notify() {

   return kTRUE;
}

void TPeacVerifierSel::Init(TTree *tree)
{
   if (!tree) return;
   fChain = tree;
}

void TPeacVerifierSel::SlaveBegin(TTree * /*tree*/)
{
   TString option = GetOption();

   fFcIn = dynamic_cast<TFileCollection*> (fInput->FindObject("PROOF_PEAC_FileCollectionIn"));

   if (fFcIn) {
      fFcOut = new TFileCollection("dummy","dummy");
      fOutput->Add(fFcOut);
   }
   TFile::Cp("root://skaf.saske.sk:1098//peac-ls.sh","peac-ls.sh");
   gSystem->Exec("chmod +x peac-ls.sh");

//   fPrefix="";

}

Bool_t TPeacVerifierSel::Process(Long64_t entry)
{
   if (!fFcIn) return kFALSE;

//   VerifyViaLs();

   VerifyViaXargs();

   return kTRUE;
}

void TPeacVerifierSel::VerifyViaLs() {
   TIter iIn(fFcIn->GetList());
   TFileInfo *fi;
   TString path;
   TInetAddress ip(gSystem->GetHostByName(TUrl(gSystem->HostName()).GetHostFQDN()));
   while ((fi = dynamic_cast<TFileInfo *>(iIn.Next()))) {
      path = TString::Format("%s%s", fPrefix.Data(),fi->GetCurrentUrl()->GetFile()).Data();
      if (path.IsNull()) continue;
      if (!gSystem->Exec(TString::Format("ls %s > /dev/null 2>&1",path.Data()).Data())) {
         path = TString::Format("root://%s/%s", ip.GetHostAddress(),fi->GetCurrentUrl()->GetFile()).Data();
         fFcOut->Add(new TFileInfo(path.Data()));
      }
   }
}

void TPeacVerifierSel::VerifyViaXargs() {
   TIter iIn(fFcIn->GetList());
   TFileInfo *fi;
   TString path;
   TInetAddress ip(gSystem->GetHostByName(TUrl(gSystem->HostName()).GetHostFQDN()));
   TString ipStr= ip.GetHostAddress();
   while ((fi = dynamic_cast<TFileInfo *>(iIn.Next()))) {
//      Printf("%s%s", fPrefix.Data(),fi->GetCurrentUrl()->GetFile());
      path = TString::Format("%s%s", fPrefix.Data(),fi->GetCurrentUrl()->GetFile()).Data();
      if (path.IsNull()) continue;
      if (ipStr.CompareTo(fi->GetCurrentUrl()->GetHost())) continue;
      gSystem->Exec(TString::Format("echo %s >> filesIn.txt",path.Data()).Data());
//      gSystem->Exec(TString::Format("echo %s >> filesOut.txt",fi->GetCurrentUrl()->GetUrl()).Data());
   }

   path = TString::Format("time cat filesIn.txt | xargs -P 0 -I {} ./peac-ls.sh {} %s %s",ip.GetHostAddress(),fPrefix.Data());
   gSystem->Exec(path.Data());



//gSystem->Exec("cat filesOut.txt");


//   if (!gSystem->Exec(TString::Format("cat filesIn.txt | xrags -P 1 -I {} ./peac-ls.sh {} %s %s",path.Data(),ip.GetHostAddress().Data(),fPrefix.Data()))) {
//      path = TString::Format("root://%s/%s", ip.GetHostAddress(),fi->GetCurrentUrl()->GetFile()).Data();
//      fFcOut->Add(new TFileInfo(path.Data()));
//   }
//   gSystem->Exec("cat filesOut.txt");
   fFcOut->AddFromFile("filesOut.txt");
}

void TPeacVerifierSel::Terminate()
{

   if (fFcOut) {
      fFcOut->SetDefaultTreeName("/aodTree");
      fFcOut->Print();
      gProof->RegisterDataSet("myDSNew",fFcOut,"O");

   }


}

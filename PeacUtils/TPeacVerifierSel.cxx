#include <TSystem.h>
#include <TCollection.h>
#include <TFileCollection.h>
#include <TFileInfo.h>
#include <THashList.h>
#include <TProof.h>
#include <TFile.h>

#include "TPeacVerifierSel.h"

TPeacVerifierSel::TPeacVerifierSel(TTree * /*tree*/) : TSelector(), fChain(0), fPrefix("/pool/data/01/xrdnamespace"), fFcIn(0), fFcOut(0)
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

   fFcIn = dynamic_cast<TFileCollection *>(fInput->FindObject("PROOF_PEAC_FileCollectionIn"));

   if (fFcIn) {
      fFcIn->Print();
      fFcOut = new TFileCollection("dummy", "dummy");
      fOutput->Add(fFcOut);
   }
   TFile::Cp("root://skaf.saske.sk:1098//peac-ls.sh", "peac-ls.sh");
   gSystem->Exec("chmod +x peac-ls.sh");

//   fPrefix="";

}

Bool_t TPeacVerifierSel::Process(Long64_t entry)
{
   if (!fFcIn) return kFALSE;

   VerifyViaLs();

//   VerifyViaXargs();

   return kTRUE;
}

void TPeacVerifierSel::VerifyViaLs() {
   TIter iIn(fFcIn->GetList());
   TFileInfo *fi;
   TFileInfo *fo;
   TString path;
   TInetAddress ip(gSystem->GetHostByName(TUrl(gSystem->HostName()).GetHostFQDN()));
   TString ipStr = ip.GetHostAddress();
   while ((fi = dynamic_cast<TFileInfo *>(iIn.Next()))) {
      path = TString::Format("%s%s", fPrefix.Data(), fi->GetCurrentUrl()->GetFile()).Data();
//      Printf("Checking url %s",fi->GetCurrentUrl()->GetUrl());

      if (path.IsNull()) continue;
//      if (ipStr.CompareTo(fi->GetCurrentUrl()->GetHost())) continue;
//      Printf("Checking url %s",path.Data());
      if (!gSystem->Exec(TString::Format("ls %s > /dev/null 2>&1", path.Data()).Data())) {
         Printf("OK url %s", fi->GetCurrentUrl()->GetUrl());
         path = TString::Format("root://%s/%s", ip.GetHostAddress(), fi->GetCurrentUrl()->GetFile()).Data();
//         fFcOut->Add(path.Data());
         fo = new TFileInfo(fi->GetCurrentUrl()->GetFile());
         fo->AddUrl(path.Data(), kTRUE);
         fFcOut->Add(fo);
         //           fFcOut->Add(new TFileInfo(fi->GetCurrentUrl()->GetUrl()));
      }
   }

}

void TPeacVerifierSel::VerifyViaXargs() {
   TIter iIn(fFcIn->GetList());
   TFileInfo *fi;
   TString path;
   TString hostIn;
   TInetAddress ip(gSystem->GetHostByName(TUrl(gSystem->HostName()).GetHostFQDN()));
   TString ipStr = ip.GetHostAddress();
   while ((fi = dynamic_cast<TFileInfo *>(iIn.Next()))) {
      path = TString::Format("%s%s", fPrefix.Data(), fi->GetCurrentUrl()->GetFile()).Data();
      hostIn = fi->GetCurrentUrl()->GetHost();
      if (path.IsNull()) continue;

//      if (hostIn.CompareTo("alice-caf.cern.ch"))
      if (ipStr.CompareTo(fi->GetCurrentUrl()->GetHost())) continue;
      gSystem->Exec(TString::Format("echo %s >> filesIn.txt", path.Data()).Data());
//      gSystem->Exec(TString::Format("echo %s >> filesOut.txt",fi->GetCurrentUrl()->GetUrl()).Data());
   }
   gSystem->Exec("cat filesIn.txt | wc -l");

   path = TString::Format("time cat filesIn.txt | xargs -P 0 -I {} ./peac-ls.sh {} %s %s", ip.GetHostAddress(), fPrefix.Data());
   gSystem->Exec(path.Data());

   gSystem->Exec("cat filesOut.txt | wc -l");


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
      fFcOut->SetAnchor("AliAOD.root");
      fFcOut->Print("");
      gProof->RegisterDataSet("myDSNew2", fFcOut, "O");


   }


}

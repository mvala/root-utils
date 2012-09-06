void TestPeacVerifier() {

//   gSystem->Load("libPeacUtils.so");

//   TProof *p = TProof::Open("skaf.saske.sk:1099","workers=1x");
//   TProof *p = TProof::Open("skaf.saske.sk","workers=1x");
   TProof *p = TProof::Open("alice-caf.cern.ch","workers=1x");
   p->UploadPackage("../pars/PeacUtils");
   if (p->EnablePackage("PeacUtils")) return;

   TProofNodes pn(p);
   TMap *filesmap = new TMap;
   TMap *nodesmap = pn.GetMapOfNodes();

   TIter nxnd(nodesmap);
   TList *wli = 0;
   TObject *obj = 0;
   Int_t kf = 1;
   while ((obj = nxnd()) != 0) {
      if ((wli = dynamic_cast<TList *>(nodesmap->GetValue(obj)))) {
         THashList *fli = new THashList;
         Int_t nf = wli->GetSize();
         TSlaveInfo *wi = (TSlaveInfo *) wli->First();
         Printf("WK: %s",wi->GetName());
         fli->Add(new TObjString(wi->GetName()));
         filesmap->Add(new TObjString(obj->GetName()), fli);
      }
   }

   filesmap->SetName("PROOF_FilesToProcess");
   p->AddInput(filesmap);

//   TFileCollection *coll = p->GetDataSet("myDS");
//   TFileCollection *coll = p->GetDataSet("myBigDS");
   TFileCollection *coll = p->GetDataSet("/PWG2/mvala/LHC11a_000146805_p4_without_SDD");

   if (!coll) return;
   coll->SetName("PROOF_PEAC_FileCollectionIn");
   p->AddInput(coll);

   p->SetParameter("PROOF_Packetizer", "TPacketizerFile");
   p->SetParameter("PROOF_ProcessNotAssigned", (Int_t)1);
   p->SetParameter("PROOF_UseMergers", "-1");
   TStopwatch timer;
   timer.Start();
   p->Process("TPeacVerifierSel", (Long64_t) 1);
   timer.Stop();
   timer.Print();
}

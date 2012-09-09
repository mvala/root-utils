void MonitorGui() {
   // Open connection to server
   TSocket *sock = new TSocket("localhost", 9090);

   // Wait till we get the start message
   char str[32];
   Int_t ret = sock->Recv(str, 32);
   Printf("%d",ret);

   if (ret>=0) {
      Printf("Str %d is %s",ret,str);
      sock->Send("Finished");
      sock->Send("Finished2");
      
   }
   
   sock->Close();
}

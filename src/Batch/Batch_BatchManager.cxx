/*
 * BatchManager.cxx : 
 *
 * Auteur : Ivan DUTKA-MALEN - EDF R&D
 * Date   : Septembre 2003
 * Projet : SALOME 2
 *
 */

#include <iostream>
#include <sstream>
#include <string>
#include <netdb.h>
//#include "MEDMEM_STRING.hxx"
#include "Batch_Job.hxx"
#include "Batch_JobId.hxx"
#include "Batch_JobInfo.hxx"
#include "Batch_InvalidArgumentException.hxx"
#include "Batch_FactBatchManager.hxx"
#include "Batch_BatchManager.hxx"
using namespace std;

namespace Batch {

  // Constructeur
//   BatchManager::BatchManager(string host) throw(InvalidArgumentException) : _hostname(host), jobid_map()
//   {
//     // On verifie que le hostname est correct
//     if (!gethostbyname(_hostname.c_str())) { // hostname unknown from network
//       string msg = "hostname \"";
//       msg += _hostname;
//       msg += "\" unknown from the network";
//       throw InvalidArgumentException(msg.c_str());
//     }
//   }
  BatchManager::BatchManager(const FactBatchManager * parent, const char * host) throw(InvalidArgumentException) : _hostname(host), jobid_map(), _parent(parent)
  {
    // On verifie que le hostname est correct
    if (!gethostbyname(_hostname.c_str())) { // hostname unknown from network
      string msg = "hostname \"";
      msg += _hostname;
      msg += "\" unknown from the network";
      throw InvalidArgumentException(msg.c_str());
    }
  }

  // Destructeur
  BatchManager::~BatchManager()
  {
    // Nothing to do
  }

  string BatchManager::__repr__() const
  {
    ostringstream oss;
    oss << "<BatchManager of type '" << (_parent ? _parent->getType() : "unknown (no factory)") << "' connected to server '" << _hostname << "'>";
    return oss.str();
  }

  // Recupere le l'identifiant d'un job deja soumis au BatchManager
//   const JobId BatchManager::getJobIdByReference(const string & ref)
//   {
//     return JobId(this, ref);
//   }
  const JobId BatchManager::getJobIdByReference(const char * ref)
  {
    return JobId(this, ref);
  }

//   // Methode pour le controle des jobs : soumet un job au gestionnaire
//   const JobId BatchManager::submitJob(const Job & job)
//   {
//     static int idx = 0;
//     //MEDMEM::STRING sst;
//     ostringstream sst;
//     sst << "Jobid_" << idx++;
//     JobId id(this, sst.str());
//     return id;
//   }

//   // Methode pour le controle des jobs : retire un job du gestionnaire
//   void BatchManager::deleteJob(const JobId & jobid)
//   {
//     // Nothing to do
//   }
   
//   // Methode pour le controle des jobs : suspend un job en file d'attente
//   void BatchManager::holdJob(const JobId & jobid)
//   {
//     // Nothing to do
//   }

//   // Methode pour le controle des jobs : relache un job suspendu
//   void BatchManager::releaseJob(const JobId & jobid)
//   {
//     // Nothing to do
//   }

//   // Methode pour le controle des jobs : modifie un job en file d'attente
//   void BatchManager::alterJob(const JobId & jobid, const Parametre & param, const Environnement & env)
//   {
//     // Nothing to do
//   }

//   // Methode pour le controle des jobs : modifie un job en file d'attente
//   void BatchManager::alterJob(const JobId & jobid, const Parametre & param)
//   {
//     // Nothing to do
//   }

//   // Methode pour le controle des jobs : modifie un job en file d'attente
//   void BatchManager::alterJob(const JobId & jobid, const Environnement & env)
//   {
//     // Nothing to do
//   }

//   // Methode pour le controle des jobs : renvoie l'etat du job
//   JobInfo BatchManager::queryJob(const JobId & jobid)
//   {
//     return JobInfo();
//   }

}
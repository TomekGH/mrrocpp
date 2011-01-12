#ifndef __INTERFACE_H
#define __INTERFACE_H

#include <QMainWindow>
#include "mainwindow.h"

#include "base/lib/sr/sr_ecp.h"
#include "base/lib/sr/sr_ui.h"
#include "base/lib/configurator.h"

#include "ui.h"

#if defined(USE_MESSIP_SRR)
#include "base/lib/messip/messip_dataport.h"
#endif

namespace mrrocpp {
namespace ui {
namespace spkm {
class UiRobot;
}
namespace common {

class UiRobot;

typedef std::map <lib::robot_name_t, UiRobot*> robots_t;
typedef robots_t::value_type robot_pair_t;

class sr_buffer;
/* TR
 class ecp_buffer;
 */
// super klasa agregujaca porozrzucane struktury


class Interface
{
private:

public:

	busy_flag communication_flag;

	sr_buffer* ui_sr_obj;
	/*TR
	 ecp_buffer* ui_ecp_obj;
	 */
	feb_thread* meb_tid;

	function_execution_buffer *main_eb;

	typedef std::string list_t;

	// listy sekcji i wezlow sieciowych plikow konfiguracyjnych
	std::list <list_t> section_list, config_node_list, all_node_list;
	// lista nazw programow i wezlow na ktorych maja byc uruchamiane
	std::list <program_node_def> program_node_list;

	int ui_node_nr; // numer wezla na ktorym jest uruchamiany UI
	pid_t ui_pid; // pid UI
	short ui_state; // 1 working, 2 exiting started, 3-5 exiting in progress - mrrocpp processes closing, 6 - exit imeditily

	TEACHING_STATE teachingstate; // dawne systemState do nauki
	TEACHING_STATE_ENUM file_window_mode;
	UI_NOTIFICATION_STATE_ENUM notification_state;

	bool is_task_window_open; // informacja czy okno zadania jest otwarte
	bool is_process_control_window_open; // informacja czy okno sterowania procesami jest otwarte
	bool process_control_window_renew; // czy okno ma zostac odswierzone

	bool is_teaching_window_open; // informacja czy okno nauki jest otwarte
	bool is_file_selection_window_open; // informacja czy okno z wyborem pliku jest otwarte

	std::ofstream *log_file_outfile;

	boost::mutex process_creation_mtx;
	lib::configurator* config;
	lib::sr_ecp* all_ecp_msg; // Wskaznik na obiekt do komunikacji z SR z fukcja ECP dla wszystkich robotow
	lib::sr_ui* ui_msg; // Wskaznik na obiekt do komunikacji z SR

	mp_state_def mp;
	// bool is_any_edp_active;
	bool is_mp_and_ecps_active;
	bool is_sr_thread_loaded;
	UI_ALL_EDPS_STATE all_edps;
	std::string config_file_relativepath; // sciezka lokalana do konfiguracji wraz z plikiem konfiguracyjnym
	std::string binaries_network_path; // sieciowa sciezka binariow mrrocpp
	std::string binaries_local_path; // lokalna sciezka binariow mrrocpp
	std::string mrrocpp_local_path; // lokalna sciezka mrrocpp: np. "/home/yoyek/mrrocpp/". W niej katalogi bin, configs etc.

	std::string teach_filesel_fullpath; // sciezka domyslana dla fileselect dla generatora uczacego
	std::string config_file;// nazwa pliku konfiguracyjnego dla UI
	std::string session_name; // nazwa sesji
	std::string config_file_fullpath; // sciezka globalna do konfiguracji


	std::string ui_attach_point;
	std::string network_sr_attach_point;
	std::string sr_attach_point;
	std::string ui_node_name; // nazwa wezla na ktorym jest uruchamiany UI

	std::string mrrocpp_bin_to_root_path;

	// The Ui robots

	/**
	 * @brief map of all robots used in the task
	 */

	common::robots_t robot_m;

	spkm::UiRobot *spkm;
	/*TR
	 smb::UiRobot *smb;
	 shead::UiRobot *shead;
	 bird_hand::UiRobot *bird_hand;
	 //robot_m[lib::] = bird_hand;

	 irp6ot_m::UiRobot *irp6ot_m;
	 irp6ot_tfg::UiRobot *irp6ot_tfg;
	 irp6p_m::UiRobot *irp6p_m;
	 irp6p_tfg::UiRobot *irp6p_tfg;
	 sarkofag::UiRobot *sarkofag;
	 irp6m::UiRobot *irp6m_m;
	 conveyor::UiRobot *conveyor;
	 speaker::UiRobot *speaker;

	 polycrank::UiRobot *polycrank;
	 */
	Interface();
	int set_ui_state_notification(UI_NOTIFICATION_STATE_ENUM new_notifacion);
	void UI_close(void);
	void init();
	int manage_interface(void);
	int MPup_int();
	void reload_whole_configuration();
	void abort_threads();
	void fill_node_list(void);
	int fill_section_list(const char *file_name_and_path);
	int initiate_configuration(void);
	int clear_all_configuration_lists(void);
	int fill_program_node_list(void);
	int get_default_configuration_file_name(void);
	int set_default_configuration_file_name(void);
	int check_edps_state_and_modify_mp_state(void);
	int check_gns(void);
	bool check_node_existence(const std::string & _node, const std::string & beginnig_of_message);
	int execute_mp_pulse(char pulse_code);

	//! TODO: throw an exception (assumed inheritance from std::exception)

	void create_threads();
	int EDP_all_robots_slay();
	int MPslay();
	int pulse_stop_mp();

	bool is_any_robot_active();
	bool are_all_robots_synchronised_or_inactive();
	bool are_all_robots_loaded_or_inactive();
	bool is_any_active_robot_loaded();

	MainWindow* mw;

};

}
}
}

#endif


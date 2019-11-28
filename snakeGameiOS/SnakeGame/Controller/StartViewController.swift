//
//  StartViewController.swift
//  SnakeGame
//
//  Created by Mihir Luthra on 16/09/18.
//  Copyright © 2018 Mihir Luthra. All rights reserved.
//

import UIKit



class StartViewController: UIViewController , scoreCard{

    @IBAction func quitGame(_ sender: UIButton) {
        exit(0)
    }
    @IBOutlet weak var score: UILabel!
    @IBAction func playGame(_ sender: UIButton) {
        performSegue(withIdentifier: "playGame", sender: self)
    }
 
    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view.
    }
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        if segue.identifier == "playGame" {
            let destinationViewController = segue.destination as! ViewController
            destinationViewController.delegate = self
//            if let num = destinationViewController.points{
//                score.text = String(num)
//            }
        }
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    @IBAction func logout(_ sender: UIButton) {
        dismiss(animated: true, completion: nil)
    }
    /*
    // MARK: - Navigation

    // In a storyboard-based application, you will often want to do a little preparation before navigation
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        // Get the new view controller using segue.destinationViewController.
        // Pass the selected object to the new view controller.
    }
    */
    
    func setScore(score: Int) {
        if score == -1 {
            self.score.text = ""
        }
        else{
            self.score.text = "Score" + String(score)
        }
    }

}

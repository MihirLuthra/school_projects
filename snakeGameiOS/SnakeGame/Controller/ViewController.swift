//
//  ViewController.swift
//  Snake Game
//
//  Created by Mihir Luthra on 13/09/18.
//  Copyright © 2018 Mihir Luthra. All rights reserved.
//

import UIKit

enum SnakeDirection{
    case right
    case left
    case down
    case up
}

enum Orientation{
    case landscape
    case portrait
}

protocol scoreCard {
    func setScore(score : Int )
}

class ViewController: UIViewController{
    
    @IBOutlet weak var scoreLabel: UILabel!
    var delegate : scoreCard?
    @IBOutlet var mainView: UIView!
    var direction : SnakeDirection = .up
    var screenOrientation : Orientation = .portrait
    var snakePartsDimension : Int = 10
    var foodDimension : Int = 10
    var gap : Int = 10
    var additionalWidthGap : Int = 0
    var additionalHeightGap : Int = 20
    var points : Int = 0
    
    @IBAction func quit(_ sender: UIButton) {
        self.delegate?.setScore(score: -1)
        dismissGame()
    }
    override func viewDidLoad() {
        super.viewDidLoad()
        snakeFunction()
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    
//    //MARK: IF PHONE MOVES
//    //if phone moves check orientation
//    override func motionBegan(_ motion: UIEventSubtype, with event: UIEvent?) {
//        screenOrientation = checkOrientation()
//    }
//    override func motionEnded(_ motion: UIEventSubtype, with event: UIEvent?) {
//        screenOrientation = checkOrientation()
//    }
//    //################################
    
    
    //MARK: CHECK ORIENTATION
    func checkOrientation() -> Orientation{
        if mainView.frame.width > mainView.frame.height{
            return .landscape
        }
        else{
            return .portrait
        }
    }
    //#######################
    
    // MARK: ADJUSTING SNAKE INNER VIEW
    func adjustSnakeInnerViewWidth(_ snakeViewWidth : Double) -> Double{
        var returnValue : Int = Int(snakeViewWidth) - ((gap + additionalWidthGap)*2)
        
        if returnValue % 2 != 0{
            returnValue -= 1
        }
        
        while returnValue % snakePartsDimension != 0{
            returnValue -= (1*2)
            additionalWidthGap += 1
        }
        return Double(returnValue)
    }
    func adjustSnakeInnerViewHeight(_ snakeViewHeight : Double) -> Double{
        var returnValue : Int = Int(snakeViewHeight) - ((gap + additionalHeightGap)*2)
        
        if returnValue % 2 != 0{
            returnValue -= 1
        }
        
        while returnValue % snakePartsDimension != 0{
            returnValue -= (1*2)
            additionalHeightGap += 1
        }
        return Double(returnValue)
    }
    //#################################
    
    //MARK: ARROW CLICKED
    @objc func arrowClicked(_ arrow: UIButton) {
        
        if arrow.tag == 1 && direction != .down{
            direction = .up
        }
        else
        if arrow.tag == 2 && direction != .up{
            direction = .down
        }
        else
        if arrow.tag == 3 && direction != .left{
            direction = .right
        }
        else
        if arrow.tag == 4 && direction != .right{
            direction = .left
        }
    }
    //##########################
    
    func snakeFunction(){
        var snake : Array = [UIView]()
        let defaultSnakeSize : Int = 7
        var snakeSize : Int = defaultSnakeSize
        var snakeX : Array = [Int]()
        var snakeY : Array = [Int]()
        
        var foodX : Int = 0
        var foodY : Int = 0
        
        var snakeViewX : Double
        var snakeViewY : Double
        
        var snakeView : UIView
        
        var snakeViewWidth : Double
        var snakeViewHeight : Double
        
        var snakeInnerView : UIView
        var snakeInnerViewWidth : Double
        var snakeInnerViewHeight : Double
        var snakeInnerViewX : Double
        var snakeInnerViewY : Double
        
        var foodView : UIView
        
        var buttonView : UIView
        
        var buttonViewWidth : Double
        var buttonViewHeight : Double
        
        var buttonViewMidHorizontal : Double
        var buttonViewMidVertical : Double
        var buttonViewY : Double
        var buttonViewX : Double
        
        var arrowUpButton : UIButton
        var arrowLeftButton : UIButton
        var arrowRightButton : UIButton
        var arrowDownButton : UIButton
        
        var arrowButtonHeight : Double
        var arrowButtonWidth : Double
        var arrowButtonUpDownX : Double
        var arrowButtonUpY : Double
        var arrowButtonDownY : Double
        var arrowButtonRightLeftY : Double
        var arrowButtonRightX : Double
        var arrowButtonLeftX : Double
        
        screenOrientation = checkOrientation()
        
        //        //MARK: BACKGROUND
        //        imgView = UIImageView(frame: CGRect( x : imgViewX , y : imgViewY , width : imgViewWidth , height : imgViewHeight ))
        //        imgView.image = #imageLiteral(resourceName: "background_1")
        //        //
        
        //MARK: SNAKE VIEW
        snakeViewX = 0
        snakeViewY = 0
        
        snakeViewWidth = Double(mainView.frame.width) - snakeViewX
        snakeViewHeight = 2*(Double(mainView.frame.height)/3) - snakeViewY
        
        snakeView = UIView(frame: CGRect( x : snakeViewX , y : snakeViewY , width : snakeViewWidth , height : snakeViewHeight ))
        snakeView.backgroundColor = .black
        //#########################
        
        //MARK: BUTTON VIEW
        buttonViewWidth = snakeViewWidth
        buttonViewHeight = snakeViewHeight/2
        
        buttonViewY = snakeViewHeight
        buttonViewX = 0
        
        buttonView = UIView(frame: CGRect( x : buttonViewX , y : buttonViewY , width : buttonViewWidth , height : buttonViewHeight ) )
        //buttonView.backgroundColor = .red
        
        buttonViewMidHorizontal = buttonViewWidth/2
        buttonViewMidVertical = buttonViewHeight/2
        //############################
        
        //MARK: SNAKE INNER VIEW
        snakeInnerViewWidth = adjustSnakeInnerViewWidth(snakeViewWidth)
        snakeInnerViewHeight = adjustSnakeInnerViewHeight(snakeViewHeight)
        
        snakeInnerViewX = Double(gap + additionalWidthGap)
        snakeInnerViewY = Double(gap + additionalHeightGap)//+20 to be in safe area
        
        snakeInnerView = UIView(frame: CGRect( x : snakeInnerViewX , y : snakeInnerViewY , width : snakeInnerViewWidth , height : snakeInnerViewHeight ))
        snakeInnerView.backgroundColor = .gray
        //##########################
        
        //MARK: FOOD VIEW
        foodX = Int(snakeInnerViewX + snakeInnerViewWidth/2)
        foodY = Int(snakeInnerViewHeight/2)
        while foodX % foodDimension != 0{
            foodX -= 1
        }
        while foodY % foodDimension != 0{
            foodY -= 1
        }
        
        foodView = UIView(frame: CGRect( x : foodX , y : foodY , width : foodDimension , height : foodDimension ))
        foodView.backgroundColor = .yellow
        
        //#######################
        
        //MARK: ARROWS BUTTONS
        arrowButtonWidth = buttonViewWidth/4
        arrowButtonHeight = buttonViewWidth/4
        
        arrowButtonUpDownX = buttonViewMidHorizontal - arrowButtonWidth/2
        arrowButtonUpY = buttonViewMidVertical - buttonViewHeight/4 - arrowButtonHeight/2
        arrowButtonDownY = (buttonViewHeight) - (arrowButtonUpY) - arrowButtonHeight
        arrowButtonRightLeftY = buttonViewMidVertical - arrowButtonHeight/2
        arrowButtonRightX = arrowButtonUpDownX + arrowButtonWidth
        arrowButtonLeftX = arrowButtonUpDownX - arrowButtonWidth
        
        arrowUpButton = UIButton(frame: CGRect( x : arrowButtonUpDownX , y : arrowButtonUpY , width : arrowButtonWidth , height : arrowButtonHeight ))
        arrowDownButton = UIButton(frame: CGRect( x : arrowButtonUpDownX , y : arrowButtonDownY , width : arrowButtonWidth , height : arrowButtonHeight ))
        arrowRightButton = UIButton(frame: CGRect( x : arrowButtonRightX , y : arrowButtonRightLeftY , width : arrowButtonWidth , height : arrowButtonHeight ))
        arrowLeftButton = UIButton(frame: CGRect( x : arrowButtonLeftX , y : arrowButtonRightLeftY , width : arrowButtonWidth , height : arrowButtonHeight ))
        
        arrowUpButton.setImage(#imageLiteral(resourceName: "up"), for: .normal)
        arrowDownButton.setImage(#imageLiteral(resourceName: "down"), for: .normal)
        arrowRightButton.setImage(#imageLiteral(resourceName: "right"), for: .normal)
        arrowLeftButton.setImage(#imageLiteral(resourceName: "left"), for: .normal)
        
        arrowUpButton.addTarget(self, action:#selector(self.arrowClicked), for: .touchUpInside)
        arrowDownButton.addTarget(self, action:#selector(self.arrowClicked), for: .touchUpInside)
        arrowRightButton.addTarget(self, action:#selector(self.arrowClicked), for: .touchUpInside)
        arrowLeftButton.addTarget(self, action:#selector(self.arrowClicked), for: .touchUpInside)
        
        arrowUpButton.tag = 1
        arrowDownButton.tag = 2
        arrowRightButton.tag = 3
        arrowLeftButton.tag = 4
        //#########################################
        
        //MARK: ADDING SUBVIEWS
        //mainView.insertSubview(imgView, at: 0)
        mainView.insertSubview(snakeView, at: 0)
        mainView.insertSubview(buttonView, at: 1)
        mainView.subviews[0].insertSubview(snakeInnerView, at: 0)
        mainView.subviews[1].insertSubview(arrowUpButton, at: 0)
        mainView.subviews[1].insertSubview(arrowDownButton, at: 1)
        mainView.subviews[1].insertSubview(arrowRightButton, at: 2)
        mainView.subviews[1].insertSubview(arrowLeftButton, at: 2)
        //mainView.subviews[0].insertSubview(foodView, at: 1)
        //mainView.subviews[0].insertSubview(foodView, aboveSubview: snakeView)
        //arrowRightButton.isUserInteractionEnabled = true
        
        //########################
        
        //MARK: INITIALIZE SNAKE
        snakeX.append(Int(Int(snakeInnerViewWidth)/(4)))
        snakeY.append(Int(snakeInnerViewHeight/2))
        while snakeX[0] % snakePartsDimension != 0{
            snakeX[0] += 1
        }
        while snakeY[0] % snakePartsDimension != 0{
            snakeY[0] -= 1
        }
        
        snake.append(UIView(frame: CGRect(x : snakeX[0] , y : snakeY[0] , width : snakePartsDimension , height : snakePartsDimension)))
        snake[0].backgroundColor = .red
        mainView.subviews[0].subviews[0].insertSubview(foodView, at: 0 )
        mainView.subviews[0].subviews[0].insertSubview(snake[0], at: 1)
        
        for i in 1...(snakeSize-1){
            snakeX.append(snakeX[i-1])
            snakeY.append(snakeY[i-1] + snakePartsDimension)
            snake.append(UIView(frame: CGRect(x : snakeX[i] , y : snakeY[i] , width : snakePartsDimension , height : snakePartsDimension)))
            snake[i].backgroundColor = .green
            mainView.subviews[0].subviews[0].insertSubview(snake[i], at: i+1)
        }
        
        
        
        
        //###########################
        
        Timer.scheduledTimer(withTimeInterval: 0.1 , repeats: true){ timer in
            
            for i in (1...(snakeSize - 1)).reversed(){
                snakeX[i] = snakeX[i-1]
                snakeY[i] = snakeY[i-1]
                snake[i].frame = CGRect(x : snakeX[i] , y : snakeY[i] , width : self.snakePartsDimension , height : self.snakePartsDimension)
            }
            
            if self.direction == .up{
                snakeY[0] -= self.snakePartsDimension
                if snakeY[0] < Int(snakeInnerViewY) - self.gap - self.additionalHeightGap{
                    snakeY[0] = Int(snakeInnerViewY + snakeInnerViewHeight) - self.snakePartsDimension - self.gap - self.additionalHeightGap
                }
            }
            else
                if self.direction == .down{
                    snakeY[0] += self.snakePartsDimension
                    if snakeY[0] >= Int(snakeInnerViewY + snakeInnerViewHeight) - self.gap - self.additionalHeightGap{
                        snakeY[0] = Int(snakeInnerViewY) - self.gap - self.additionalHeightGap
                    }
                    //snake[0].frame = CGRect(x : snakeX[0] , y : snakeY[0] , width : self.snakePartsDimension , height : self.snakePartsDimension)
                }
                else
                    if self.direction == .right{
                        snakeX[0] += self.snakePartsDimension
                        if snakeX[0] >= Int(snakeInnerViewX + snakeInnerViewWidth) - self.gap - self.additionalWidthGap{
                            snakeX[0] = Int(snakeInnerViewX) - self.gap - self.additionalWidthGap
                        }
                        //snake[0].frame = CGRect(x : snakeX[0] , y : snakeY[0] , width : self.snakePartsDimension , height : self.snakePartsDimension)
                    }
                    else
                        if self.direction == .left{
                            snakeX[0] -= self.snakePartsDimension
                            if snakeX[0] < Int(snakeInnerViewX) - self.gap - self.additionalWidthGap{
                                snakeX[0] = Int(snakeInnerViewX + snakeInnerViewWidth) - self.gap - self.additionalWidthGap - self.snakePartsDimension
                            }
                            //snake[0].frame = CGRect(x : snakeX[0] , y : snakeY[0] , width : self.snakePartsDimension , height : self.snakePartsDimension)
            }
            snake[0].frame = CGRect(x : snakeX[0] , y : snakeY[0] , width : self.snakePartsDimension , height : self.snakePartsDimension)
            
            if snakeX[0] == foodX && snakeY[0] == foodY{
                snakeSize += 1
                snakeX.append(snakeX[snakeSize-2])
                snakeY.append(snakeY[snakeSize-2])
                snake.append(UIView(frame: CGRect(x : snakeX[snakeSize-1] , y : snakeY[snakeSize-1] , width : self.snakePartsDimension , height : self.snakePartsDimension)))
                snake[snakeSize-1].backgroundColor = .green
                self.mainView.subviews[0].subviews[0].insertSubview(snake[snakeSize-1], at: snakeSize-1)
                
                foodX = Int(arc4random_uniform(UInt32(snakeInnerViewWidth)))
                foodY = Int(arc4random_uniform(UInt32(snakeInnerViewHeight)))
                while foodX % self.foodDimension != 0{
                    foodX -= 1
                }
                
                while foodY % self.foodDimension != 0{
                    foodY -= 1
                }
                self.mainView.subviews[0].subviews[0].subviews[0].frame = CGRect( x : foodX , y : foodY , width : self.foodDimension , height : self.foodDimension)
            }
            self.scoreLabel.text = "Score: " + String(snakeSize - defaultSnakeSize)
            for i in 1...(snakeSize - 1){
                if (snakeX[i] == snakeX[0]) && (snakeY[i]==snakeY[0]){
                    snake[i].removeFromSuperview()
                    self.points = snakeSize - defaultSnakeSize
                    //self.delegate?.setScore(score: self.points)
                    Timer.scheduledTimer(withTimeInterval: 2 , repeats: true){ timer in
                        //self.dismiss(animated: true, completion: nil)
                        self.dismissGame()
                    }
                    timer.invalidate()
                }
            }
        }
    }
    
    func dismissGame(){
        self.dismiss(animated: true, completion: nil)
    }

    
}


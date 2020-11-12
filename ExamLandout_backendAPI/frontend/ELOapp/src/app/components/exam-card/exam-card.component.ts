import { Component, OnInit, Input } from '@angular/core';

import { ExamCard } from '../../models/examCard';

@Component({
  selector: 'app-exam-card',
  templateUrl: './exam-card.component.html',
  styleUrls: ['./exam-card.component.scss']
})
export class ExamCardComponent implements OnInit {

  @Input()
  examCard: ExamCard;

  constructor() { }

  ngOnInit() {

  }

  ngAfterViewInit(){
    console.log(this.examCard);
  }




}
